#include "GlobalData.h"



GlobalData* GlobalData::singleton_= nullptr;

GlobalData::GlobalData()
{
    //ctor
}

GlobalData::~GlobalData()
{
    if (signalBuffer != nullptr)   delete signalBuffer;

}


 GlobalData *GlobalData::GetInstance()
 {
     if(singleton_== nullptr){
        singleton_ = new GlobalData();
    }
    return singleton_;

 }

bool  GlobalData::copySignalBuffer(int* sourceData, int size)
{
    // Minimum check on the data to be copied
    if (sourceData == nullptr)  return false;

    if (size <= 0 || size > MAX_BUFFER_SIZE)  return false;

     if (signalBuffer == nullptr)
        signalBuffer = new int[size];

    for (int i=0;i<size; i++)
    {
        int nextSample = sourceData[i];
        signalBuffer[i] = sourceData[i];
    }


     bufferSize = size;

     return true;
}

