#include <pluginlib/class_list_macros.h>
#include "../include/dbx_base.h"
#include "../include/dbx_plugin.h"

//注册插件
//导入宏定义    参数1：子类   参数2：父类
PLUGINLIB_EXPORT_CLASS(dbx_plugin_ns::SanBian , dbx_base_ns::Dbx_Base);
PLUGINLIB_EXPORT_CLASS(dbx_plugin_ns::SiBian , dbx_base_ns::Dbx_Base);