#ifndef dDBX_PLUGIN
#define dDBX_PLUGIN
#include"dbx_base.h"
namespace dbx_plugin_ns
{
  //正三角形
   class SanBian : public dbx_base_ns::Dbx_Base
   {
    public:
         SanBian()
         {
            m_side_length = 0.0;
         }
         virtual void init(double side_length)
         {
            this->m_side_length = side_length;
         }
          virtual double getlength()
          {
             return m_side_length *3 ;
          }
    private:
       double m_side_length;

   };
   //四边形

   class SiBian : public dbx_base_ns::Dbx_Base
   {
    public:
         SiBian()
         {
            m_side_length = 0.0;
         }
         virtual void init(double side_length)
         {
            this->m_side_length = side_length;
         }
          virtual double getlength()
          {
             return m_side_length *4 ;
          }
    private:
       double m_side_length;
   };
   

}


#endif