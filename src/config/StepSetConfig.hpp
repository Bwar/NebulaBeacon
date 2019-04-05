/*******************************************************************************
 * Project:  Beacon
 * @file     StepSetConfig.hpp
 * @brief
 * @author   Bwar
 * @date:    2019-04-04
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDREGISTER_STEPSETCONFIG_HPP_
#define SRC_CMDREGISTER_STEPSETCONFIG_HPP_

#include <util/http/http_parser.h>
#include <util/json/CJsonObject.hpp>
#include <pb/neb_sys.pb.h>
#include <actor/step/PbStep.hpp>
#include "BeaconError.hpp"
#include "SessionOnlineNodes.hpp"

namespace beacon
{

class StepSetConfig: public neb::PbStep,
    public neb::DynamicCreator<StepSetConfig, std::shared_ptr<SessionOnlineNodes>,
                               std::shared_ptr<neb::SocketChannel>, int32, int32, int32,
                               std::string, std::string, std::string>
{
public:
    StepSetConfig(
            std::shared_ptr<SessionOnlineNodes> pSessionOnlineNodes,
            std::shared_ptr<neb::SocketChannel> pChannel,
            int32 iHttpMajor,
            int32 iHttpMinor,
            int32 iCmd,
            const std::string& strNodeType,
            const std::string& strNodeIdentify,
            const std::string& strConfigFileContent,
            const std::string& strConfigFileRelativePath="",
            const std::string& strConfigFileName="");
    virtual ~StepSetConfig();

    virtual neb::E_CMD_STATUS Emit(
            int iErrno = 0,
            const std::string& strErrMsg = "",
            void* data = NULL);

    virtual neb::E_CMD_STATUS Callback(
            std::shared_ptr<neb::SocketChannel> pChannel,
            const MsgHead& oInMsgHead,
            const MsgBody& oInMsgBody,
            void* data = NULL);

    virtual neb::E_CMD_STATUS Timeout();

private:
    std::shared_ptr<SessionOnlineNodes> m_pSessionOnlineNodes;
    std::shared_ptr<neb::SocketChannel> m_pChannel;
    int32 m_iEmitNum;
    int32 m_iSetResultCode;
    int32 m_iHttpMajor;
    int32 m_iHttpMinor;
    int32 m_iCmd;
    std::string m_strNodeType;
    std::string m_strNodeIdentify;
    std::string m_strConfigFileContent;
    std::string m_strConfigFileRelativePath;
    std::string m_strConfigFileName;
    neb::CJsonObject m_oSetResultMsg;
};

} /* namespace beacon */

#endif /* SRC_CMDREGISTER_STEPSETCONFIG_HPP_ */
