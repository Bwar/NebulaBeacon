/*******************************************************************************
 * Project:  Beacon
 * @file     CmdElection.cpp
 * @brief 
 * @author   bwar
 * @date:    2019-1-6
 * @note
 * Modify history:
 ******************************************************************************/
#include "CmdElection.hpp"
#include <channel/SocketChannel.hpp>

namespace beacon
{

CmdElection::CmdElection(int32 iCmd)
    : neb::Cmd(iCmd), m_pSessionOnlineNodes(nullptr)
{
}

CmdElection::~CmdElection()
{
}

bool CmdElection::Init()
{
    return(true);
}

bool CmdElection::AnyMessage(std::shared_ptr<neb::SocketChannel> pChannel,
                const MsgHead& oMsgHead,
                const MsgBody& oMsgBody)
{
    Election oElection;
    if (nullptr == m_pSessionOnlineNodes)
    {
        m_pSessionOnlineNodes = std::dynamic_pointer_cast<SessionOnlineNodes>(GetSession("beacon::SessionOnlineNodes"));
        if (nullptr == m_pSessionOnlineNodes)
        {
            LOG4_ERROR("no session node found!");
            return(false);
        }
    }
    if (oElection.ParseFromString(oMsgBody.data()))
    {
        m_pSessionOnlineNodes->AddBeaconBeat(pChannel->GetIdentify(), oElection);
        return(true);
    }
    else
    {
        LOG4_ERROR("failed to parse election info from MsgBody.data()!");
        return(false);
    }
}

} /* namespace beacon */
