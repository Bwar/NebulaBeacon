/*******************************************************************************
 * Project:  Beacon
 * @file     StepGetConfig.hpp
 * @brief
 * @author   Bwar
 * @date:    2019-04-01
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_CMDREGISTER_STEPGETCONFIG_HPP_
#define SRC_CMDREGISTER_STEPGETCONFIG_HPP_

#include <util/http/http_parser.h>
#include <util/json/CJsonObject.hpp>
#include <pb/neb_sys.pb.h>
#include <actor/step/PbStep.hpp>

namespace beacon
{

class StepGetConfig: public neb::PbStep,
    public neb::DynamicCreator<StepGetConfig, std::shared_ptr<neb::SocketChannel>, int32, int32, int32, std::string, std::string, std::string>
{
public:
    StepGetConfig(
            std::shared_ptr<neb::SocketChannel> pChannel,
            int32 iHttpMajor,
            int32 iHttpMinor,
            int32 iCmd,
            const std::string& strNodeIdentify,
            const std::string& strConfigFileRelativePath="",
            const std::string& strConfigFileName="");
    virtual ~StepGetConfig();

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
    std::shared_ptr<neb::SocketChannel> m_pChannel;
    int32 m_iHttpMajor;
    int32 m_iHttpMinor;
    int32 m_iCmd;
    std::string m_strNodeIdentify;
    std::string m_strConfigFileRelativePath;
    std::string m_strConfigFileName;
};

} /* namespace beacon */

#endif /* SRC_CMDREGISTER_STEPGETCONFIG_HPP_ */
