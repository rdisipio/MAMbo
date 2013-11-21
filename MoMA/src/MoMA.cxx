#include "MoMA.h"

MoMATool::MoMATool()
{

}

MoMATool::~MoMATool()
{

}


///////////////////////////////////////////


MoMATool * MoMATool::GetHandle()
{
   static MoMATool instance;

   return &instance;
}
