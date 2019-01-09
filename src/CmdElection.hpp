/*******************************************************************************
 * Project:  Beacon
 * @file     CmdElection.hpp
 * @brief 
 * @author   bwar
 * @date:    2019-1-6
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDNODEREPORT_CMDNODEREPORT_HPP_
#define SRC_CMDNODEREPORT_CMDNODEREPORT_HPP_

#include <actor/cmd/Cmd.hpp>
#include <Error.hpp>
#include <SessionOnlineNodes.hpp>

namespace beacon
{

class CmdElection: public neb::Cmd, public neb::DynamicCreator<CmdElection, int32>
{
public:
    CmdElection(int32 iCmd);
    virtual ~CmdElection();

    virtual bool Init();
    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pUpstreamChannel,
                    const MsgHead& oMsgHead,
                    const MsgBody& oMsgBody);

private:
    std::shared_ptr<SessionOnlineNodes> m_pSessionOnlineNodes;
};

} /* namespace beacon */

#endif /* SRC_CMDNODEREPORT_CMDNODEREPORT_HPP_ */
