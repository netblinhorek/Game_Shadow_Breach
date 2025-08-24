// NativeMethods.h
#pragma once

#include <windows.h>

namespace CppCLRWinFormsProject {

    using namespace System;
    using namespace System::Runtime::InteropServices;

    public ref class NativeMethods
    {
    public:
        [DllImport("user32.dll", CharSet = CharSet::Ansi)]
            static extern bool EnumDisplaySettingsA(
                [MarshalAs(UnmanagedType::LPStr)] String^ deviceName,
                int modeNum,
                [Out] DEVMODE% devMode);

        [DllImport("user32.dll", CharSet = CharSet::Ansi)]
            static extern int ChangeDisplaySettingsA(
                [In] DEVMODE% devMode,
                int flags);

        [StructLayout(LayoutKind::Sequential, CharSet = CharSet::Ansi)]
            public value struct DEVMODE
        {
            [MarshalAs(UnmanagedType::ByValTStr, SizeConst = 32)]
                public String dmDeviceName;
            public short dmSpecVersion;
            public short dmDriverVersion;
            public short dmSize;
            public short dmDriverExtra;
            public int dmFields;
            public int dmPositionX;
            public int dmPositionY;
            public int dmDisplayOrientation;
            public int dmDisplayFixedOutput;
            public short dmColor;
            public short dmDuplex;
            public short dmYResolution;
            public short dmTTOption;
            public short dmCollate;
            [MarshalAs(UnmanagedType::ByValTStr, SizeConst = 32)]
                public String dmFormName;
            public short dmLogPixels;
            public int dmBitsPerPel;
            public int dmPelsWidth;
            public int dmPelsHeight;
            public int dmDisplayFlags;
            public int dmDisplayFrequency;
            public int dmICMMethod;
            public int dmICMIntent;
            public int dmMediaType;
            public int dmDitherType;
            public int dmReserved1;
            public int dmReserved2;
            public int dmPanningWidth;
            public int dmPanningHeight;
        };
    };
}