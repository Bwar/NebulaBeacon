/*******************************************************************************
 * Project:  NebulaBeacon
 * @file     ModuleAdmin.hpp
 * @brief    Nebula集群管理
 * @author   Bwar
 * @date:    2018年12月8日
 * @note     
 * Modify history:
 ******************************************************************************/
#ifndef MODULEADMIN_HPP
#define MODULEADMIN_HPP

#include <string>
#include <Error.hpp>
#include <util/json/CJsonObject.hpp>
#include <actor/cmd/Module.hpp>
#include "SessionOnlineNodes.hpp"
#include "BeaconError.hpp"

namespace beacon
{

/**
 * @brief 集群管理
 * @note 集群管理通过将命令和参数封在JSON体并填充http body，再post到Beacon节点。
 * 命令管理的JSON体格式如下：
 * {
 *     "cmd":"show",
 *     "args":["ip_white"]
 * }
 *
 * 命令帮助：
 *     show:
 *         show ip_white
 *         show subscription
 *         show subscription ${node_type}
 *         show nodes
 *         show nodes ${node_type}
 *         show node_report ${node_type}
 *         show node_report ${node_type} ${node_identify}
 *         show node_detail ${node_type}
 *         show node_detail ${node_type} ${node_identify}
 *         show beacon
 *     get:
 *         get node_config ${node_identify}
 *         get node_custom_config ${node_identify}
 *         get custom_config ${node_identify} ${config_file_relative_path} ${config_file_name}
 *     set:
 *         set node_config ${node_type} ${config_file_content}
 *         set node_config ${node_type} ${node_identify} ${config_file_content}
 *         set node_config_from_file ${node_type} ${config_file}
 *         set node_config_from_file ${node_type} ${node_identify} ${config_file}
 *         set node_custom_config ${node_type} ${config_content}
 *         set node_custom_config ${node_type} ${node_identify} ${config_content}
 *         set node_custom_config_from_file ${node_type} ${config_file}
 *         set node_custom_config_from_file ${node_type} ${node_identify} ${config_file}
 *         set custom_config ${node_type} ${config_file_name} ${config_file_content}
 *         set custom_config ${node_type} ${config_file_relative_path} ${config_file_name} ${config_file_content}
 *         set custom_config ${node_type} ${node_identify} ${config_file_relative_path} ${config_file_name} ${config_file_content}
 *         set custom_config_from_file ${node_type} ${config_file}
 *         set custom_config_from_file ${node_type} ${config_file_relative_path} ${config_file}
 *         set custom_config_from_file ${node_type} ${node_identify} ${config_file_relative_path} ${config_file}
 */ 
class ModuleAdmin: public neb::Module, public neb::DynamicCreator<ModuleAdmin, std::string&>
{
public:
    ModuleAdmin(const std::string& strModulePath);
    virtual ~ModuleAdmin();

    virtual bool Init();

    virtual bool AnyMessage(
                    std::shared_ptr<neb::SocketChannel> pChannel,
                    const HttpMsg& oHttpMsg);
protected:
    void ResponseOptions(
            std::shared_ptr<neb::SocketChannel> pChannel, const HttpMsg& oInHttpMsg);
    void Show(neb::CJsonObject& oCmdJson, neb::CJsonObject& oResult) const;
    void Get(std::shared_ptr<neb::SocketChannel> pChannel,
            int32 iHttpMajor, int32 iHttpMinor,
            neb::CJsonObject& oCmdJson, neb::CJsonObject& oResult);
    void Set(std::shared_ptr<neb::SocketChannel> pChannel,
            int32 iHttpMajor, int32 iHttpMinor,
            neb::CJsonObject& oCmdJson, neb::CJsonObject& oResult);

private:
    std::shared_ptr<SessionOnlineNodes> m_pSessionOnlineNodes;
};

} /* namespace beacon */

#endif /* MODULEADMIN_HPP */

