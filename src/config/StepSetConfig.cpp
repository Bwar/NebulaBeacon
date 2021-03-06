/*******************************************************************************
 * Project:  Beacon
 * @file     StepSetConfig.cpp
 * @brief 
 * @author   Bwar
 * @date:    2019-04-04
 * @note
 * Modify history:
 ******************************************************************************/
#include "StepSetConfig.hpp"
#include <util/encrypt/base64.h>
#include <channel/SocketChannel.hpp>

namespace beacon
{

StepSetConfig::StepSetConfig(
        std::shared_ptr<SessionOnlineNodes> pSessionOnlineNodes,
        std::shared_ptr<neb::SocketChannel> pChannel,
        int32 iHttpMajor,
        int32 iHttpMinor,
        int32 iCmd,
        const std::string& strNodeType,
        const std::string& strNodeIdentify,
        const std::string& strConfigFileContent,
        const std::string& strConfigFileRelativePath,
        const std::string& strConfigFileName)
    : m_pSessionOnlineNodes(pSessionOnlineNodes), m_pChannel(pChannel),
      m_iEmitNum(0), m_iSetResultCode(0),
      m_iHttpMajor(iHttpMajor), m_iHttpMinor(iHttpMinor),
      m_iCmd(iCmd),
      m_strNodeType(strNodeType),
      m_strNodeIdentify(strNodeIdentify),
      m_strConfigFileContent(strConfigFileContent),
      m_strConfigFileRelativePath(strConfigFileRelativePath),
      m_strConfigFileName(strConfigFileName)
{
    m_oSetResultMsg.Parse("{}");
}

StepSetConfig::~StepSetConfig()
{
}

neb::E_CMD_STATUS StepSetConfig::Emit(int iErrno, const std::string& strErrMsg, void* data)
{
    MsgBody oMsgBody;
    neb::ConfigInfo oConfigFileInfo;
    int iDecodeLen = Base64decode_len(m_strConfigFileContent.c_str());
    char* pBufPlain = (char*)malloc(iDecodeLen);
    int iDecodeBytes = Base64decode(pBufPlain, m_strConfigFileContent.c_str());
    oConfigFileInfo.set_file_name(m_strConfigFileName);
    oConfigFileInfo.set_file_content(pBufPlain, iDecodeBytes);
    oConfigFileInfo.set_file_path(m_strConfigFileRelativePath);
    oMsgBody.set_data(oConfigFileInfo.SerializeAsString());
    free(pBufPlain);

    HttpMsg oHttpMsg;
    oHttpMsg.set_type(HTTP_RESPONSE);
    oHttpMsg.set_status_code(200);
    oHttpMsg.set_http_major(m_iHttpMajor);
    oHttpMsg.set_http_minor(m_iHttpMinor);
    neb::CJsonObject oResponseData;
    if (m_strNodeIdentify.size() > 0)
    {
        if (SendTo(m_strNodeIdentify, m_iCmd, GetSequence(), oMsgBody))
        {
            ++m_iEmitNum;
            return(neb::CMD_STATUS_RUNNING);
        }
        else
        {
            oResponseData.Add("code", ERR_NODE_IDENTIFY);
            oResponseData.Add("msg", "unknow identify \"" + m_strNodeIdentify + "\"!");
            oHttpMsg.set_body(oResponseData.ToFormattedString());
            SendTo(m_pChannel, oHttpMsg);
            return(neb::CMD_STATUS_FAULT);
        }
    }
    else if (m_strNodeType.size() > 0)
    {
        std::vector<std::string> vecNodes;
        if (m_pSessionOnlineNodes->GetOnlineNode(m_strNodeType, vecNodes))
        {
            for (auto it = vecNodes.begin(); it != vecNodes.end(); ++it)
            {
                if (SendTo(*it, m_iCmd, GetSequence(), oMsgBody))
                {
                    ++m_iEmitNum;
                }
                else
                {
                    m_iSetResultCode |= ERR_NODE_IDENTIFY;
                    m_oSetResultMsg.Add(*it, "connect failed");
                }
            }
            if (m_iEmitNum == 0)
            {
                oResponseData.Add("code", ERR_INVALID_ARGV);
                oResponseData.Add("msg", "failed");
                oResponseData.Add("data", m_oSetResultMsg);
                oHttpMsg.set_body(oResponseData.ToFormattedString());
                SendTo(m_pChannel, oHttpMsg);
                return(neb::CMD_STATUS_FAULT);
            }
            return(neb::CMD_STATUS_RUNNING);
        }
        else
        {
            oResponseData.Add("code", ERR_INVALID_ARGV);
            oResponseData.Add("msg", "There are no nodes of this type!");
            oHttpMsg.set_body(oResponseData.ToFormattedString());
            SendTo(m_pChannel, oHttpMsg);
            return(neb::CMD_STATUS_FAULT);
        }
    }
    else
    {
        oResponseData.Add("code", ERR_INVALID_ARGV);
        oResponseData.Add("msg", "miss node type!");
        oHttpMsg.set_body(oResponseData.ToFormattedString());
        SendTo(m_pChannel, oHttpMsg);
        return(neb::CMD_STATUS_FAULT);
    }
}

neb::E_CMD_STATUS StepSetConfig::Callback(std::shared_ptr<neb::SocketChannel> pChannel, const MsgHead& oInMsgHead, const MsgBody& oInMsgBody, void* data)
{
    --m_iEmitNum;
    m_iSetResultCode |= oInMsgBody.rsp_result().code();
    m_oSetResultMsg.Add(pChannel->GetIdentify(), oInMsgBody.rsp_result().msg());
    if (0 == m_iEmitNum)
    {
        HttpMsg oHttpMsg;
        oHttpMsg.set_type(HTTP_RESPONSE);
        oHttpMsg.set_status_code(200);
        oHttpMsg.set_http_major(m_iHttpMajor);
        oHttpMsg.set_http_minor(m_iHttpMinor);
        neb::CJsonObject oResponseData;
        if (neb::ERR_OK == m_iSetResultCode)
        {
            oResponseData.Add("code", neb::ERR_OK);
            oResponseData.Add("msg", "success");
        }
        else
        {
            oResponseData.Add("code", m_iSetResultCode);
            oResponseData.Add("msg", "failed");
            oResponseData.Add("data", m_oSetResultMsg);
        }
        oHttpMsg.set_body(oResponseData.ToFormattedString());
        SendTo(m_pChannel, oHttpMsg);
        return(neb::CMD_STATUS_COMPLETED);
    }
    else
    {
        return(neb::CMD_STATUS_RUNNING);
    }
}

neb::E_CMD_STATUS StepSetConfig::Timeout()
{
    HttpMsg oHttpMsg;
    oHttpMsg.set_type(HTTP_RESPONSE);
    oHttpMsg.set_status_code(200);
    oHttpMsg.set_http_major(m_iHttpMajor);
    oHttpMsg.set_http_minor(m_iHttpMinor);
    neb::CJsonObject oResponseData;
    oResponseData.Add("code", neb::ERR_TIMEOUT);
    oResponseData.Add("msg", "get config file timeout!");
    oHttpMsg.set_body(oResponseData.ToFormattedString());
    SendTo(m_pChannel, oHttpMsg);
    return(neb::CMD_STATUS_FAULT);
}

} /* namespace beacon */
