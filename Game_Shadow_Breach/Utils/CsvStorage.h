#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

namespace CppCLRWinFormsProject {

    public ref class CsvStorage abstract sealed
    {
    public:
        literal wchar_t* DefaultFile = L"C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\game_results.csv";

        static void AppendRow(array<String^>^ columns, String^ filePath)
        {
            Directory::CreateDirectory(Path::GetDirectoryName(filePath));
            String^ line = String::Join(",", columns);
            File::AppendAllText(filePath, line + Environment::NewLine);
        }

        static void AppendRow(array<String^>^ columns)
        {
            AppendRow(columns, gcnew String(DefaultFile));
        }

        static array<array<String^>^>^ ReadAll(String^ filePath)
        {
            if (!File::Exists(filePath)) return gcnew array<array<String^>^>(0);
            array<String^>^ lines = File::ReadAllLines(filePath);
            List<array<String^>^>^ rows = gcnew List<array<String^>^>();
            for each (String ^ line in lines)
            {
                rows->Add(line->Split(','));
            }
            return rows->ToArray();
        }
    };
} 