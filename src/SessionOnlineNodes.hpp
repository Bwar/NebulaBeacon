/*******************************************************************************
 * Project:  Beacon
 * @file     SessionOnlineNodes.hpp
 * @brief 
 * @author   bwar
 * @date:    Sep 20, 2016
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_SESSIONNODESHOLDER_HPP_
#define SRC_SESSIONNODESHOLDER_HPP_

#include <cstring>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <actor/session/Session.hpp>
#include <util/json/CJsonObject.hpp>
#include "beacon.pb.h"
#include "StepNodeBroadcast.hpp"

namespace beacon
{

/**
 * @brief report node status
 * @note node info：
 * {
 *     "node_type":"ACCESS",
 *     "node_ip":"192.168.11.12",
 *     "node_port":9988,
 *     "gate_ip":"120.234.2.106",
 *     "gate_port":10001,
 *     "node_id":0,
 *     "worker_num":10,
 *     "active_time":16879561651.06,
 *     "node":{
 *         "load":1885792, "connect":495873, "recv_num":98755266, "recv_byte":98856648832, "sent_num":154846322, "sent_byte":648469320222,"client":495870
 *     },
 *     "worker":
 *     [
 *          {"load":655666, "connect":495873, "recv_num":98755266, "recv_byte":98856648832, "sent_num":154846322, "sent_byte":648469320222,"client":195870}},
 *          {"load":655235, "connect":485872, "recv_num":98755266, "recv_byte":98856648832, "sent_num":154846322, "sent_byte":648469320222,"client":195870}},
 *          {"load":585696, "connect":415379, "recv_num":98755266, "recv_byte":98856648832, "sent_num":154846322, "sent_byte":648469320222,"client":195870}}
 *     ]
 * }
 */

class SessionOnlineNodes: public neb::Session, neb::DynamicCreator<SessionOnlineNodes, double>
{
public:
    SessionOnlineNodes(double dSessionTimeout);
    virtual ~SessionOnlineNodes();

    virtual neb::E_CMD_STATUS Timeout();

public:
    void InitElection(const neb::CJsonObject& oBeacon);
    void AddIpwhite(const std::string& strIpwhite);
    void AddSubscribe(const std::string& strNodeType, const std::string& strSubscribeNodeType);

    /**
     * @return node_id
     */
    uint16 AddNode(const neb::CJsonObject& oNodeInfo);
    void RemoveNode(const std::string& strNodeIdentify);
    void AddBeaconBeat(const std::string& strNodeIdentify, const Election& oElection);
    void BeaconFailed(const std::string& strNodeIdentify);

    void GetIpWhite(neb::CJsonObject& oIpWhite) const;
    void GetBeacon(neb::CJsonObject& oBeacon) const;
    void GetSubscription(neb::CJsonObject& oSubcription) const;
    void GetSubscription(const std::string& strNodeType, neb::CJsonObject& oSubcription) const;
    void GetOnlineNode(neb::CJsonObject& oOnlineNode) const;
    void GetOnlineNode(const std::string& strNodeType, neb::CJsonObject& oOnlineNode) const;
    bool GetNodeReport(const std::string& strNodeType, neb::CJsonObject& oNodeReport) const;
    bool GetNodeReport(const std::string& strNodeType, const std::string& strIdentify, neb::CJsonObject& oNodeReport) const;

    bool GetOnlineNode(const std::string& strNodeType, std::vector<std::string>& vecNodes);

protected:
    void AddNodeBroadcast(const neb::CJsonObject& oNodeInfo);
    void RemoveNodeBroadcast(const neb::CJsonObject& oNodeInfo);
    void CheckLeader();
    void SendBeaconBeat();

private:
    static const uint32 sc_uiLeader;
    static const uint32 sc_uiAlive;
    uint16 m_unLastNodeId;
    bool m_bIsLeader;
    std::unordered_set<uint16> m_setNodeId;
    std::unordered_set<uint16> m_setAddedNodeId;
    std::unordered_set<uint16> m_setRemovedNodeId;
    std::unordered_set<std::string> m_setIpwhite;
    std::unordered_map<std::string, std::unordered_set<std::string> > m_mapPublisher;               ///< map<node_type, set<subscribers_node_type> >
    std::unordered_map<std::string, uint16> m_mapIdentifyNodeId;                          ///< map<node_identify, node_id>
    std::unordered_map<std::string, std::string> m_mapIdentifyNodeType;                   ///< map<node_Identify，node_type>
    std::unordered_map<std::string, std::unordered_map<std::string, neb::CJsonObject> > m_mapNode;  ///< map<node_type, map<node_identify, neb::CJsonObject> >
    std::map<std::string, uint32> m_mapBeacon;
};

}

#endif /* SRC_SESSIONNODESHOLDER_HPP_ */
