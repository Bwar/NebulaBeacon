/*******************************************************************************
 * Project:  Beacon
 * @file     SessionOnlineNodes.cpp
 * @brief 
 * @author   bwar
 * @date:    Sep 20, 2016
 * @note
 * Modify history:
 ******************************************************************************/

#include "Definition.hpp"
#include "SessionOnlineNodes.hpp"

namespace beacon
{

SessionOnlineNodes::SessionOnlineNodes()
    : neb::Session("beacon::SessionOnlineNodes", neb::gc_dNoTimeout),
      m_unLastNodeId(0)
{
}

SessionOnlineNodes::~SessionOnlineNodes()
{
}

neb::E_CMD_STATUS SessionOnlineNodes::Timeout()
{
    return(neb::CMD_STATUS_RUNNING);
}

void SessionOnlineNodes::AddIpwhite(const std::string& strIpwhite)
{
    m_setIpwhite.insert(strIpwhite);
}

void SessionOnlineNodes::AddSubscribe(const std::string& strNodeType, const std::string& strSubscribeNodeType)
{
    auto pub_iter = m_mapPublisher.find(strSubscribeNodeType);
    if (pub_iter == m_mapPublisher.end())
    {
        std::unordered_set<std::string> setSubscriber;
        setSubscriber.insert(strNodeType);
        m_mapPublisher.insert(std::make_pair(strSubscribeNodeType, setSubscriber));
    }
    else
    {
        pub_iter->second.insert(strNodeType);
    }
}

uint16 SessionOnlineNodes::AddNode(const neb::CJsonObject& oNodeInfo)
{
    LOG4_TRACE("(%s)", oNodeInfo.ToString().c_str());
    uint32 uiNodeId = 0;
    std::unordered_set<uint16>::iterator node_id_iter;
    std::string strNodeIdentify = oNodeInfo("node_ip") + std::string(":") + oNodeInfo("node_port");
    neb::CJsonObject oNodeInfoWithNodeId = oNodeInfo;
    oNodeInfo.Get("node_id", uiNodeId);

    // find node_id or create node_id
    auto identify_node_iter = m_mapIdentifyNodeId.find(strNodeIdentify);
    if (identify_node_iter == m_mapIdentifyNodeId.end())
    {
        while (0 == uiNodeId)
        {
            uiNodeId = ++m_unLastNodeId;
            node_id_iter = m_setNodeId.find(uiNodeId);
            if (node_id_iter != m_setNodeId.end())
            {
                uiNodeId = 0;
            }
            if (m_setNodeId.size() >= 65535)
            {
                LOG4_ERROR("there is no valid node_id in the system!");
                return(0);
            }
        }
        m_mapIdentifyNodeId.insert(std::make_pair(strNodeIdentify, uiNodeId));
    }
    else
    {
        uiNodeId = identify_node_iter->second;
    }
    oNodeInfoWithNodeId.Replace("node_id", uiNodeId);


    auto node_type_iter = m_mapNode.find(oNodeInfoWithNodeId("node_type"));
    if (node_type_iter == m_mapNode.end())
    {
        std::unordered_map<std::string, neb::CJsonObject> mapNodeInfo;
        mapNodeInfo.insert(std::make_pair(strNodeIdentify, oNodeInfoWithNodeId));
        m_mapNode.insert(std::make_pair(oNodeInfoWithNodeId("node_type"), mapNodeInfo));
        m_mapIdentifyNodeType.insert(std::make_pair(strNodeIdentify, oNodeInfoWithNodeId("node_type")));
        m_setNodeId.insert(uiNodeId);
        AddNodeBroadcast(oNodeInfoWithNodeId);
        return(uiNodeId);
    }
    else
    {
        auto node_iter = node_type_iter->second.find(strNodeIdentify);
        if (node_iter == node_type_iter->second.end())
        {
            node_type_iter->second.insert(std::make_pair(strNodeIdentify, oNodeInfoWithNodeId));
            m_setNodeId.insert(uiNodeId);
            m_mapIdentifyNodeType.insert(std::make_pair(strNodeIdentify, oNodeInfoWithNodeId("node_type")));
            AddNodeBroadcast(oNodeInfoWithNodeId);
            return(uiNodeId);
        }
        else
        {
            node_iter->second = oNodeInfoWithNodeId;
            m_setNodeId.insert(uiNodeId);
            return(uiNodeId);
        }
    }
}

void SessionOnlineNodes::RemoveNode(const std::string& strNodeIdentify)
{
    LOG4_TRACE("%s", __FUNCTION__);
    auto identity_node_iter = m_mapIdentifyNodeType.find(strNodeIdentify);
    if (identity_node_iter != m_mapIdentifyNodeType.end())
    {
        auto node_type_iter = m_mapNode.find(identity_node_iter->second);
        if (node_type_iter != m_mapNode.end())
        {
            auto node_iter = node_type_iter->second.find(strNodeIdentify);
            if (node_iter != node_type_iter->second.end())
            {
                uint32 uiNodeId = 0;
                node_iter->second.Get("node_id", uiNodeId);
                RemoveNodeBroadcast(node_iter->second);
                m_setNodeId.erase(uiNodeId);
                m_mapIdentifyNodeType.erase(strNodeIdentify);
                node_type_iter->second.erase(node_iter);
            }
        }
    }
}

void SessionOnlineNodes::GetIpWhite(neb::CJsonObject& oIpWhite) const
{
    oIpWhite.Parse("[]");
    for (auto it = m_setIpwhite.begin(); it != m_setIpwhite.end(); ++it)
    {
        oIpWhite.Add(*it);
    }
}

void SessionOnlineNodes::GetSubscription(neb::CJsonObject& oSubcription) const
{
    /**
     * oSubcription like this: 
     * [
     *     {"node_type":"INTERFACE", "subcriber":["LOGIC", "LOGGER"]},
     *     {"node_type":"LOGIC", "subcriber":["LOGIC", "MYDIS", "LOGGER"]}
     * ]
     */
    oSubcription.Parse("[]");
    for (auto pub_iter = m_mapPublisher.begin();
            pub_iter != m_mapPublisher.end(); ++pub_iter)
    {
        oSubcription.AddAsFirst(neb::CJsonObject("{}"));
        oSubcription[0].Add("node_type", pub_iter->first);
        oSubcription[0].AddEmptySubArray("subcriber");
        for (auto it = pub_iter->second.begin(); it != pub_iter->second.end(); ++it)
        {
            oSubcription[0]["subcriber"].Add(*it);
        }
    }
}

void SessionOnlineNodes::GetSubscription(const std::string& strNodeType, neb::CJsonObject& oSubcription) const
{
    /**
     * oSubcription like this: 
     * [
     *     "INTERFACE", "ACCESS"
     * ]
     */
    oSubcription.Parse("[]");
    auto pub_iter = m_mapPublisher.find(strNodeType);
    if (pub_iter != m_mapPublisher.end())
    {
        for (auto it = pub_iter->second.begin(); it != pub_iter->second.end(); ++it)
        {
            oSubcription.Add(*it);
        }
    }
}

void SessionOnlineNodes::GetOnlineNode(neb::CJsonObject& oOnlineNode) const
{
    /**
     * oOnlineNode like this: 
     * [
     *     {"node_type":"INTERFACE", "node":["192.168.157.131:16004", "192.168.157.132:16004"]},
     *     {"node_type":"LOGIC", "node":["192.168.157.131:16005", "192.168.157.132:16005"]},
     *     {"node_type":"DBAGENT", "node":["192.168.157.131:16007", "192.168.157.132:16007"]}
     * ]
     */
    oOnlineNode.Parse("[]");
    for (auto node_iter = m_mapNode.begin(); node_iter != m_mapNode.end(); ++node_iter)
    {
        oOnlineNode.AddAsFirst(neb::CJsonObject("{}"));
        oOnlineNode[0].Add("node_type", node_iter->first);
        oOnlineNode[0].AddEmptySubArray("node");
        for (auto it = node_iter->second.begin(); it != node_iter->second.end(); ++it)
        {
            oOnlineNode[0]["node"].Add(it->second("node_ip") + ":" + it->second("node_port"));
        }
    }
}

void SessionOnlineNodes::GetOnlineNode(
        const std::string& strNodeType, neb::CJsonObject& oOnlineNode) const
{
    /**
     * oOnlineNode like this: 
     * [
     *     "192.168.157.131:16005", "192.168.157.132:16005"
     * ]
     */
    oOnlineNode.Parse("[]");
    auto node_iter = m_mapNode.find(strNodeType);
    if (node_iter != m_mapNode.end())
    {
        for (auto it = node_iter->second.begin(); it != node_iter->second.end(); ++it)
        {
            oOnlineNode.Add(it->second("node_ip") + ":" + it->second("node_port"));
        }
    }
}

bool SessionOnlineNodes::GetNodeReport(
        const std::string& strNodeType, neb::CJsonObject& oNodeReport) const
{
    auto node_iter = m_mapNode.find(strNodeType);
    if (node_iter == m_mapNode.end())
    {
        return(false);
    }
    else
    {
        oNodeReport.Parse("[]");
        for (auto it = node_iter->second.begin(); it != node_iter->second.end(); ++it)
        {
            oNodeReport.AddAsFirst(it->second);
            oNodeReport[0].Delete("worker");
        }
        return(true);
    }
}

bool SessionOnlineNodes::GetNodeReport(
        const std::string& strNodeType,
        const std::string& strIdentify,
        neb::CJsonObject& oNodeReport) const
{
    auto node_iter = m_mapNode.find(strNodeType);
    if (node_iter == m_mapNode.end())
    {
        return(false);
    }
    else
    {
        auto it = node_iter->second.find(strIdentify);
        if (it == node_iter->second.end())
        {
            return(false);
        }
        else
        {
            oNodeReport = it->second;
            return(true);
        }
    }
}

void SessionOnlineNodes::AddNodeBroadcast(const neb::CJsonObject& oNodeInfo)
{
    LOG4_TRACE("(%s)", oNodeInfo.ToString().c_str());
    std::unordered_map<std::string, std::unordered_map<std::string, neb::CJsonObject> >::iterator node_list_iter;
    std::unordered_map<std::string, neb::CJsonObject>::iterator node_iter;
    std::unordered_set<std::string>::iterator node_type_iter;
    neb::CJsonObject oSubcribeNodeInfo;
    neb::CJsonObject oAddNodes;
    neb::CJsonObject oAddedNodeInfo = oNodeInfo;
    oAddedNodeInfo.Delete("node");
    oAddedNodeInfo.Delete("worker");
    oAddNodes.Add("add_nodes", neb::CJsonObject("[]"));
    oAddNodes["add_nodes"].Add(oAddedNodeInfo);
    oSubcribeNodeInfo.Add("add_nodes", neb::CJsonObject("[]"));
    for (auto sub_iter = m_mapPublisher.begin();
                    sub_iter != m_mapPublisher.end(); ++sub_iter)
    {
        for (node_type_iter = sub_iter->second.begin(); node_type_iter != sub_iter->second.end(); ++node_type_iter)
        {
            /* send this node info to subscriber */
            if (sub_iter->first == oNodeInfo("node_type"))
            {
                node_list_iter = m_mapNode.find(*node_type_iter);
                if (node_list_iter != m_mapNode.end())
                {
                    LOG4_TRACE("m_mapNode[%s].size() = %u", node_type_iter->c_str(), node_list_iter->second.size());
                    try
                    {
                        for (node_iter = node_list_iter->second.begin(); node_iter != node_list_iter->second.end(); ++node_iter)
                        {
                            if (node_iter->second("node_id") == oNodeInfo("node_id"))
                            {
                                continue;
                            }

                            MsgBody oMsgBody;
                            oMsgBody.set_data(oAddNodes.ToString());
                            std::shared_ptr<neb::Step> pStep = MakeSharedStep("beacon::StepNodeBroadcast", node_iter->first, (int32)neb::CMD_REQ_NODE_NOTICE, oMsgBody);
                            if (nullptr != pStep)
                            {
                                pStep->Emit();
                            }
                        }
                    }
                    catch(std::bad_alloc& e)
                    {
                        LOG4_ERROR("new StepNodeBroadcast error: %s", e.what());
                    }
                }
            }

            /* make subscribe node info */
            if ((*node_type_iter) == oNodeInfo("node_type"))
            {
                node_list_iter = m_mapNode.find(sub_iter->first);
                if (node_list_iter != m_mapNode.end())
                {
                    for (node_iter = node_list_iter->second.begin(); node_iter != node_list_iter->second.end(); ++node_iter)
                    {
                        neb::CJsonObject oExistNodeInfo = node_iter->second;
                        oExistNodeInfo.Delete("node");
                        oExistNodeInfo.Delete("worker");
                        oSubcribeNodeInfo["add_nodes"].Add(oExistNodeInfo);
                    }
                }
            }

        }
    }

    /* send subscribe node info to this node */
    if (oSubcribeNodeInfo["add_nodes"].GetArraySize() > 0)
    {
        try
        {
            MsgBody oMsgBody;
            char szThisNodeIdentity[32] = {0};
            oMsgBody.set_data(oSubcribeNodeInfo.ToString());
            snprintf(szThisNodeIdentity, sizeof(szThisNodeIdentity),
                            "%s:%s", oNodeInfo("node_ip").c_str(), oNodeInfo("node_port").c_str());
            std::shared_ptr<neb::Step> pStep = MakeSharedStep("beacon::StepNodeBroadcast", std::string(szThisNodeIdentity), (int32)neb::CMD_REQ_NODE_NOTICE, oMsgBody);
            if (nullptr != pStep)
            {
                pStep->Emit();
            }
        }
        catch(std::bad_alloc& e)
        {
            LOG4_ERROR("new StepNodeBroadcast error: %s", e.what());
        }
    }
}

void SessionOnlineNodes::RemoveNodeBroadcast(const neb::CJsonObject& oNodeInfo)
{
    LOG4_TRACE("(%s)", oNodeInfo.ToString().c_str());
    std::unordered_map<std::string, std::unordered_map<std::string, neb::CJsonObject> >::iterator node_list_iter;
    std::unordered_map<std::string, neb::CJsonObject>::iterator node_iter;
    std::unordered_set<std::string>::iterator node_type_iter;
    neb::CJsonObject oDelNodes;
    neb::CJsonObject oDeletedNodeInfo = oNodeInfo;
    oDeletedNodeInfo.Delete("node");
    oDeletedNodeInfo.Delete("worker");
    oDelNodes.Add("del_nodes", neb::CJsonObject("[]"));
    oDelNodes["del_nodes"].Add(oDeletedNodeInfo);
    for (auto sub_iter = m_mapPublisher.begin();
                    sub_iter != m_mapPublisher.end(); ++sub_iter)
    {
        for (node_type_iter = sub_iter->second.begin(); node_type_iter != sub_iter->second.end(); ++node_type_iter)
        {
            /* send this node info to subscriber */
            if (sub_iter->first == oNodeInfo("node_type"))
            {
                node_list_iter = m_mapNode.find(*node_type_iter);
                if (node_list_iter != m_mapNode.end())
                {
                    for (node_iter = node_list_iter->second.begin(); node_iter != node_list_iter->second.end(); ++node_iter)
                    {
                        MsgBody oMsgBody;
                        oMsgBody.set_data(oDelNodes.ToString());
                        std::shared_ptr<neb::Step> pStep = MakeSharedStep("beacon::StepNodeBroadcast", node_iter->first, (int32)neb::CMD_REQ_NODE_NOTICE, oMsgBody);
                        if (nullptr != pStep)
                        {
                            pStep->Emit();
                        }
                    }
                }
            }
        }
    }
}

}
