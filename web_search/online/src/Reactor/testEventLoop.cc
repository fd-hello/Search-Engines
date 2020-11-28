#include "EchoServer.h"
#include "TcpConnection.h"
#include "../../include/WebPageQuery.h"
#include "../../include/configuration.h"
#include "../../include/loadFile.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void onConnection(const TcpConnectionPtr & conn)
{
    cout<<">>"<<conn->toString()<<" has connected!"<<endl;
    /* conn->send("Welcome to Server!"); */
}

void onMessage(const TcpConnectionPtr &conn, Threadpool* threadpool, Configuration & conf,loadFile *lf)
{
    string msg=conn->receive();
    cout<<">>> receive:"<<msg<<endl;
    
    
    //交给处理任务线程
    WebPageQuery mytask(msg,conn,conf,lf);
    threadpool->addTask(std::bind(&WebPageQuery::doQuery,mytask));    
}

void onClose(const TcpConnectionPtr &conn)
{
    cout<<">>"<<conn->toString()<<" has closed!"<<endl;
}



int main(int argc,char *argv[])
{
    
    EchoServer server(4,10,"192.168.75.128",2000);

    Configuration conf("../conf/path.conf");

    loadFile *lf=loadFile::getInstance();//获取到单例类对象
    lf->loadPageLib(conf.getConfigMap()["repage_path"],conf.getConfigMap()["reoffset_path"],conf);
    lf->loadInvertIndexTable(conf.getConfigMap()["invertIndex_path"]);

    server.setConnectionCallBack(onConnection);
    server.setMessageCallBack(std::bind(onMessage,std::placeholders::_1,server.getThreadpool(),conf,lf));
    server.setCloseCallBack(onClose);

    server.start();

    return 0;
}

