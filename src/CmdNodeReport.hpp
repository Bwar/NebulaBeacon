/*******************************************************************************
 * Project:  Beacon
 * @file     CmdNodeReport.hpp
 * @brief 
 * @author   bwar
 * @date:    Feb 14, 2017
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDNODEREPORT_CMDNODEREPORT_HPP_
#define SRC_CMDNODEREPORT_CMDNODEREPORT_HPP_

#include <util/json/CJsonObject.hpp>
#include <actor/cmd/Cmd.hpp>
#include <Error.hpp>
#include <SessionOnlineNodes.hpp>

namespace beacon
{

class CmdNodeReport: public neb::Cmd, public neb::DynamicCreator<CmdNodeReport, int32>
{
public:
    CmdNodeReport(int32 iCmd);
    virtual ~CmdNodeReport();

    virtual bool Init();
    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pChannel,
                    const MsgHead& oMsgHead,
                    const MsgBody& oMsgBody);

private:
    std::shared_ptr<SessionOnlineNodes> m_pSessionOnlineNodes;
};

} /* namespace beacon */

#endif /* SRC_CMDNODEREPORT_CMDNODEREPORT_HPP_ */
