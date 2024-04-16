#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#define   MAX_BUFFER_SIZE    10000


class GlobalData
{

    protected:
        GlobalData();
        virtual ~GlobalData();

         static GlobalData* singleton_;

     public:
         static GlobalData *GetInstance();

        unsigned int getBufferSize()       {   return bufferSize;   }
        int * getSignalBuffer()            {   return signalBuffer; }

        bool  copySignalBuffer(int* sourceData, int size);

    private:
          int *signalBuffer = nullptr;
          unsigned int bufferSize = 0;

};



#endif // GLOBALDATA_H
