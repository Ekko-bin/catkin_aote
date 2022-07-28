#ifndef DOBX_H
#define DOBX_H


namespace dbx_base_ns
{
    //必须保证基类包含无参构造函数
    
    class Dbx_Base
    {
      public:
          Dbx_Base(){}
          //计算周长的函数
        virtual double getlength() = 0;
          //初始化周长的函数
        virtual void init(double side_length) = 0;
    };
}



#endif