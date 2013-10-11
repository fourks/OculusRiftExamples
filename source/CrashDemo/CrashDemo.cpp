#ifdef WIN32
#include <Windows.h>
#define SAY(X) OutputDebugString(X)
#else
#include <iostream>
#define SAY(X) std::cout << X << std::endl
#endif

#include "OVR.h"

// This application crashes with 0.2.5 of the Oculus SDK with the following stack trace:
//
//CrashDemo [C/C++ Application]
//    CrashDemo [22194] [cores: 1]
//        Thread [1] 22194 [core: 1] (Suspended : Signal : SIGSEGV:Segmentation fault)
//            OVR::CircularBuffer<OVR::Vector3<float> >::CircularBuffer() at OVR_SensorFilter.h:44 0x428a1b
//            OVR::SensorFilterBase<OVR::Vector3<float> >::SensorFilterBase() at OVR_SensorFilter.h:92 0x427198
//            OVR::SensorFilter::SensorFilter() at OVR_SensorFilter.h:191 0x426d3e
//            OVR::SensorFusion::SensorFusion() at OVR_SensorFusion.cpp:37 0x422ef3
//            CrashDemo::CrashDemo() at CrashDemo.cpp:12 0x421632
//            main() at CrashDemo.cpp:29 0x421404
//    gdb
//
// The problem is obfuscated somewhat because it's occuring inside the code generated by the
// OVR_ALLOC macro, which invokes OVR::Allocator::GetInstance(), which returns null until
// OVR::System::Init() has been called;
//

class CrashDemo {
protected:
    OVR::SensorFusion sensorFusion;

public:
    CrashDemo() {
        SAY("ctor");
        // do the master initialization for the Oculus VR SDK
        OVR::System::Init();
    }

    ~CrashDemo() {
        SAY("ctor");
        OVR::System::Destroy();
    }

    int run() {
        SAY("Run method");
    }
};

// Windows has a non-standard main function prototype
#ifdef WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(int argc, char ** argv) {
#endif
    CrashDemo demo;
    demo.run();
}