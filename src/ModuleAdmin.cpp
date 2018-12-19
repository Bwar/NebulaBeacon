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
                std::shared_ptr<neb::SocketChannel> pUpstreamChannel,
                const HttpMsg& oInHttpMsg)
{
    if (HTTP_OPTIONS == oInHttpMsg.method())
    {
        LOG4_TRACE("receive an OPTIONS");
        ResponseOptions(pUpstreamChannel, oInHttpMsg);
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
        SendTo(pUpstreamChannel, oHttpMsg);
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
            SendTo(pUpstreamChannel, oHttpMsg);
            return(false);
        }
    }

    if (std::string("show") == oCmdJson("cmd") || std::string("SHOW") == oCmdJson("cmd"))
    {
        Show(oCmdJson, oResponseData);
    }
    else
    {
        oResponseData.Add("code", ERR_INVALID_CMD);
        oResponseData.Add("msg",
                std::string("invalid cmd \"") + oCmdJson("cmd") + std::string("\" !"));
    }

    oHttpMsg.set_body(oResponseData.ToFormattedString());
    SendTo(pUpstreamChannel, oHttpMsg);
    return(true);
}

void ModuleAdmin::ResponseOptions(std::shared_ptr<neb::SocketChannel> pUpstreamChannel, const HttpMsg& oInHttpMsg)
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
    SendTo(pUpstreamChannel, oHttpMsg);
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
                oResult.Add("code", ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetSubscription(oCmdJson["args"](1), oResult["data"]);
            }
            else if (std::string("nodes") == oCmdJson["args"](0))
            {
                oResult.Add("code", ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetOnlineNode(oCmdJson["args"](1), oResult["data"]);
            }
            else if (std::string("node_report") == oCmdJson["args"](0))
            {
                oResult.Add("code", ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetNodeReport(oCmdJson["args"](1), oResult["data"]);
            }
            else if (std::string("node_detail") == oCmdJson["args"](0))
            {
                oResult.Add("code", ERR_OK);
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
                oResult.Add("code", ERR_OK);
                oResult.Add("msg", std::string("success."));
                oResult.AddEmptySubArray("data");
                m_pSessionOnlineNodes->GetNodeReport(oCmdJson["args"](1), oCmdJson["args"](2), oResult["data"]);
            }
            else if (std::string("node_detail") == oCmdJson["args"](0))
            {
                oResult.Add("code", ERR_OK);
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

} /* namespace beacon */

