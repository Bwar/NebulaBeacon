/*******************************************************************************
 * Project:  NebulaBeacon
 * @file     ModuleAdmin.cpp
 * @brief 
 * @author   Bwar
 * @date:    2018年12月8日
 * @note
 * Modify history:
 ******************************************************************************/
#include "ModuleAdmin.hpp"

namespace beacon
{

ModuleAdmin::ModuleAdmin(const std::string& strModulePath)
    : neb::Module(strModulePath), m_pSessionOnlineNodes(nullptr)
{
}

ModuleAdmin::~ModuleAdmin()
{
}

bool ModuleAdmin::Init()
{
    return(true);
}

bool ModuleAdmin::AnyMessage(
                std::shared_ptr<neb::SocketChannel> pChannel,
                const HttpMsg& oInHttpMsg)
{
    if (HTTP_OPTIONS == oInHttpMsg.method())
    {
        LOG4_TRACE("receive an OPTIONS");
        ResponseOptions(pChannel, oInHttpMsg);
        return(true);
    }

    HttpMsg oHttpMsg;
    oHttpMsg.set_type(HTTP_RESPONSE);
    oHttpMsg.set_status_code(200);
    oHttpMsg.set_http_major(oInHttpMsg.http_major());
    oHttpMsg.set_http_minor(oInHttpMsg.http_minor());
    neb::CJsonObject oResponseData;
    neb::CJsonObject oCmdJson;
    if (!oCmdJson.Parse(oInHttpMsg.body()))
    {
        oResponseData.Add("code", neb::ERR_BODY_JSON);
        oResponseData.Add("msg", "error json format!");
        oHttpMsg.set_body(oResponseData.ToFormattedString());
        SendTo(pChannel, oHttpMsg);
        return(false);
    }
    if (nullptr == m_pSessionOnlineNodes)
    {
        m_pSessionOnlineNodes = std::dynamic_pointer_cast<SessionOnlineNodes>(GetSession("beacon::SessionOnlineNodes"));
        if (nullptr == m_pSessionOnlineNodes)
        {
            LOG4_ERROR("no session node found!");
            oResponseData.Add("code", ERR_SERVICE);
            oResponseData.Add("msg", "no session node found!");
            oHttpMsg.set_body(oResponseData.ToFormattedString());
            SendTo(pChannel, oHttpMsg);
            return(false);
        }
    }

    if (std::string("show") == oCmdJson("cmd") || std::string("SHOW") == oCmdJson("cmd"))
    {
        Show(oCmdJson, oResponseData);
    }
    else if (std::string("get") == oCmdJson("cmd") || std::string("GET") == oCmdJson("cmd"))
    {
        Get(pChannel, oInHttpMsg.http_major(), oInHttpMsg.http_minor(), oCmdJson, oResponseData);
    }
    else if (std::string("set") == oCmdJson("cmd") || std::string("SET") == oCmdJson("cmd"))
    {
        Set(pChannel, oInHttpMsg.http_major(), oInHttpMsg.http_minor(), oCmdJson, oResponseData);
    }
    else
    {
        oResponseData.Add("code", ERR_INVALID_CMD);
        oResponseData.Add("msg",
                std::string("invalid cmd \"") + oCmdJson("cmd") + std::string("\" !"));
    }

    if (oResponseData.IsEmpty())
    {
        return(true);
    }

    oHttpMsg.set_body(oResponseData.ToFormattedString());
    SendTo(pChannel, oHttpMsg);
    return(true);
}

void ModuleAdmin::ResponseOptions(std::shared_ptr<neb::SocketChannel> pChannel, const HttpMsg& oInHttpMsg)
{
    LOG4_DEBUG("%s()", __FUNCTION__);
    HttpMsg oHttpMsg;
    oHttpMsg.set_type(HTTP_RESPONSE);
    oHttpMsg.set_status_code(200);
    oHttpMsg.set_http_major(oInHttpMsg.http_major());
    oHttpMsg.set_http_minor(oInHttpMsg.http_minor());
    oHttpMsg.mutable_headers()->insert(google::protobuf::MapPair<std::string, std::string>("Connection", "keep-alive"));
    oHttpMsg.mutable_headers()->insert(google::protobuf::MapPair<std::string, std::string>("Access-Control-Allow-Origin", "*"));
    oHttpMsg.mutable_headers()->insert(google::protobuf::MapPair<std::string, std::string>("Access-Control-Allow-Headers", "Origin, Content-Type, Cookie, Accept"));
    oHttpMsg.mutable_headers()->insert(google::protobuf::MapPair<std::string, std::string>("Access-Control-Allow-Methods", "GET, POST"));
    oHttpMsg.mutable_headers()->insert(google::protobuf::MapPair<std::string, std::string>("Access-Control-Allow-Credentials", "true"));
    SendTo(pChannel, oHttpMsg);
}

void ModuleAdmin::Show(neb::CJsonObject& oCmdJson, neb::CJsonObject& oResult) const
{
    switch (oCmdJson["args"].GetArraySize())
    {
        case 0:
            oResult.Add("code", ERR_INVALID_ARGC);
            oResult.Add("msg", std::string("invalid arguments num for \"")
                    + oCmdJson("cmd") + std::string("\"!"));
            break;
        case 1:
            if (std::string("ip_white") == oCmdJson["args"](0))
            {
                oResult.Add("code", ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetIpWhite(oResult["data"]);
            }
            else if (std::string("subscription") == oCmdJson["args"](0))
            {
                oResult.Add("code", ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetSubscription(oResult["data"]);
            }
            else if (std::string("nodes") == oCmdJson["args"](0))
            {
                oResult.Add("code", ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetOnlineNode(oResult["data"]);
            }
            else if (std::string("beacon") == oCmdJson["args"](0))
            {
                oResult.Add("code", (int32)neb::ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetBeacon(oResult["data"]);
            }
            else
            {
                oResult.Add("code", ERR_INVALID_ARGV);
                oResult.Add("msg", std::string("invalid arguments \"")
                        + oCmdJson["args"](0) + std::string("\" !"));
            }
            break;
        case 2:
            if (std::string("subscription") == oCmdJson["args"](0))
            {
                oResult.Add("code", (int32)neb::ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetSubscription(oCmdJson["args"](1), oResult["data"]);
            }
            else if (std::string("nodes") == oCmdJson["args"](0))
            {
                oResult.Add("code", (int32)neb::ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetOnlineNode(oCmdJson["args"](1), oResult["data"]);
            }
            else if (std::string("node_report") == oCmdJson["args"](0))
            {
                oResult.Add("code", (int32)neb::ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetNodeReport(oCmdJson["args"](1), oResult["data"]);
            }
            else if (std::string("node_detail") == oCmdJson["args"](0))
            {
                oResult.Add("code", (int32)neb::ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetNodeReport(oCmdJson["args"](1), oResult["data"]);
            }
            else
            {
                oResult.Add("code", ERR_INVALID_ARGV);
                oResult.Add("msg", std::string("invalid arguments \"")
                        + oCmdJson["args"](0) + std::string("\" !"));
            }
            break;
        case 3:
            if (std::string("node_report") == oCmdJson["args"](0))
            {
                oResult.Add("code", (int32)neb::ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetNodeReport(oCmdJson["args"](1), oCmdJson["args"](2), oResult["data"]);
            }
            else if (std::string("node_detail") == oCmdJson["args"](0))
            {
                oResult.Add("code", (int32)neb::ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetNodeReport(oCmdJson["args"](1), oCmdJson["args"](2), oResult["data"]);
            }
            else
            {
                oResult.Add("code", ERR_INVALID_ARGV);
                oResult.Add("msg", "invalid arguments num or invalid arguments!");
            }
            break;
        default:
            oResult.Add("code", ERR_INVALID_ARGC);
            oResult.Add("msg", std::string("invalid arguments num for \"")
                    + oCmdJson("cmd") + " " + oCmdJson["args"](0) + std::string("\" !"));
    }
}

void ModuleAdmin::Get(std::shared_ptr<neb::SocketChannel> pChannel,
        int32 iHttpMajor, int32 iHttpMinor,
        neb::CJsonObject& oCmdJson, neb::CJsonObject& oResult)
{
    if (std::string("node_config") == oCmdJson["args"](0))
    {
        if (oCmdJson["args"].GetArraySize() == 2)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepGetConfig", pChannel, iHttpMajor, iHttpMinor,
                    (int32)neb::CMD_REQ_GET_NODE_CONFIG,
                    oCmdJson["args"](1), std::string(""), std::string(""));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else
        {
            oResult.Add("code", ERR_INVALID_ARGV);
            oResult.Add("msg", "invalid arguments num or invalid arguments!");
        }
    }
    else if (std::string("node_custom_config") == oCmdJson["args"](0))
    {
        if (oCmdJson["args"].GetArraySize() == 2)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepGetConfig", pChannel, iHttpMajor, iHttpMinor,
                    (int32)neb::CMD_REQ_GET_NODE_CUSTOM_CONFIG,
                    oCmdJson["args"](1), std::string(""), std::string(""));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else
        {
            oResult.Add("code", ERR_INVALID_ARGV);
            oResult.Add("msg", "invalid arguments num or invalid arguments!");
        }
    }
    else if (std::string("custom_config") == oCmdJson["args"](0))
    {
        if (oCmdJson["args"].GetArraySize() == 4)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepGetConfig", pChannel, iHttpMajor, iHttpMinor,
                    (int32)neb::CMD_REQ_GET_CUSTOM_CONFIG,
                    oCmdJson["args"](1), oCmdJson["args"](2), oCmdJson["args"](3));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else
        {
            oResult.Add("code", ERR_INVALID_ARGV);
            oResult.Add("msg", "invalid arguments num or invalid arguments!");
        }
    }
    else
    {
        oResult.Add("code", ERR_INVALID_ARGV);
        oResult.Add("msg", "invalid arguments num or invalid arguments!");
    }
}

void ModuleAdmin::Set(std::shared_ptr<neb::SocketChannel> pChannel,
        int32 iHttpMajor, int32 iHttpMinor,
        neb::CJsonObject& oCmdJson, neb::CJsonObject& oResult)
{
    if (std::string("node_config") == oCmdJson["args"](0)
            || std::string("node_config_from_file") == oCmdJson["args"](0)
            || std::string("node_custom_config") == oCmdJson["args"](0)
            || std::string("node_custom_config_from_file") == oCmdJson["args"](0))
    {
        int32 iCmd = neb::CMD_REQ_SET_NODE_CONFIG;
        if (std::string("node_custom_config") == oCmdJson["args"](0)
                || std::string("node_custom_config_from_file") == oCmdJson["args"](0))
        {
            iCmd = neb::CMD_REQ_SET_NODE_CUSTOM_CONFIG;
        }
        if (oCmdJson["args"].GetArraySize() == 3)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepSetConfig", m_pSessionOnlineNodes,
                    pChannel, iHttpMajor, iHttpMinor,
                    iCmd, oCmdJson["args"](1), std::string(""),
                    oCmdJson["args"][2].ToString(), std::string(""), std::string(""));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else if (oCmdJson["args"].GetArraySize() == 4)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepSetConfig", m_pSessionOnlineNodes,
                    pChannel, iHttpMajor, iHttpMinor,
                    iCmd, oCmdJson["args"](1),
                    oCmdJson["args"](2), oCmdJson["args"][3].ToString(), 
                    std::string(""), std::string(""));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else
        {
            oResult.Add("code", ERR_INVALID_ARGV);
            oResult.Add("msg", "invalid arguments num or invalid arguments!");
        }
    }
    else if (std::string("custom_config") == oCmdJson["args"](0)
            || std::string("custom_config_from_file") == oCmdJson["args"](0))
    {
        int32 iCmd = neb::CMD_REQ_SET_CUSTOM_CONFIG;
        if (oCmdJson["args"].GetArraySize() == 4)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepSetConfig", m_pSessionOnlineNodes,
                    pChannel, iHttpMajor, iHttpMinor,
                    iCmd, oCmdJson["args"](1), std::string(""),
                    oCmdJson["args"](3), std::string(""), oCmdJson["args"](2));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else if (oCmdJson["args"].GetArraySize() == 5)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepSetConfig", m_pSessionOnlineNodes,
                    pChannel, iHttpMajor, iHttpMinor,
                    iCmd, oCmdJson["args"](1), std::string(""), oCmdJson["args"](4),
                    oCmdJson["args"](2), oCmdJson["args"](3));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else if (oCmdJson["args"].GetArraySize() == 6)
        {
            std::shared_ptr<neb::Step> pStep = MakeSharedStep(
                    "beacon::StepSetConfig", m_pSessionOnlineNodes,
                    pChannel, iHttpMajor, iHttpMinor,
                    iCmd, oCmdJson["args"](1), oCmdJson["args"](2), oCmdJson["args"](5),
                    oCmdJson["args"](3), oCmdJson["args"](4));
            if (nullptr == pStep)
            {
                oResult.Add("code", (int32)neb::ERR_NEW);
                oResult.Add("msg", "server internal error!");
            }
            else
            {
                pStep->Emit();
            }
        }
        else
        {
            oResult.Add("code", ERR_INVALID_ARGV);
            oResult.Add("msg", "invalid arguments num or invalid arguments!");
        }
    }
    else
    {
        oResult.Add("code", ERR_INVALID_ARGV);
        oResult.Add("msg", "invalid arguments num or invalid arguments!");
    }
}

} /* namespace beacon */

