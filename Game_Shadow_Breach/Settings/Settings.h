#pragma once

namespace CppCLRWinFormsProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Settings : public System::Windows::Forms::Form
    {
    public:
        Settings(void)
        {
            InitializeComponent();
            LoadSettings(); // Загружаем текущие настройки
        }

    protected:
        ~Settings()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ buttonBack;
        System::Windows::Forms::GroupBox^ groupBoxGraphics;
        System::Windows::Forms::ComboBox^ comboBoxResolution;
        System::Windows::Forms::Label^ labelResolution;
        System::Windows::Forms::CheckBox^ checkBoxFullscreen;
        System::Windows::Forms::TrackBar^ trackBarVolume;
        System::Windows::Forms::Label^ labelVolume;
        System::Windows::Forms::Label^ labelVolumeValue;
        System::Windows::Forms::GroupBox^ groupBoxAudio;
        System::Windows::Forms::Button^ buttonSave;
        System::Windows::Forms::Button^ buttonCancel;
        System::Windows::Forms::Panel^ panelContainer;

        // Новые элементы управления
        System::Windows::Forms::ComboBox^ comboBoxQuality;
        System::Windows::Forms::Label^ labelQuality;
        System::Windows::Forms::CheckBox^ checkBoxVSync;
        System::Windows::Forms::TrackBar^ trackBarMusic;
        System::Windows::Forms::Label^ labelMusic;
        System::Windows::Forms::Label^ labelMusicValue;
        System::Windows::Forms::CheckBox^ checkBoxSubtitles;
        System::Windows::Forms::ComboBox^ comboBoxLanguage;

    private:
        System::ComponentModel::Container^ components;

        // Метод для загрузки текущих настроек
        void LoadSettings()
        {
            // Здесь будет код загрузки настроек из файла/реестра
            comboBoxResolution->SelectedIndex = 0;
            comboBoxQuality->SelectedIndex = 2; // Высокое качество по умолчанию
            comboBoxLanguage->SelectedIndex = 0;
            trackBarVolume->Value = 80;
            trackBarMusic->Value = 70;
            checkBoxFullscreen->Checked = false;
            checkBoxVSync->Checked = true;
            checkBoxSubtitles->Checked = true;
        }

        // Метод для сохранения настроек
        void SaveSettings()
        {
            // Здесь будет код сохранения настроек в файл/реестр
            String^ resolution = comboBoxResolution->Text;
            int volume = trackBarVolume->Value;
            int musicVolume = trackBarMusic->Value;
            bool fullscreen = checkBoxFullscreen->Checked;
            bool vsync = checkBoxVSync->Checked;
            bool subtitles = checkBoxSubtitles->Checked;
            String^ quality = comboBoxQuality->Text;
            String^ language = comboBoxLanguage->Text;

            // В реальном проекте здесь бы сохранялись в конфиг файл
            MessageBox::Show(String::Format(
                "Настройки сохранены!\nРазрешение: {0}\nКачество: {1}\nГромкость: {2}%\nМузыка: {3}%\nПолный экран: {4}\nVSync: {5}\nСубтитры: {6}\nЯзык: {7}",
                resolution, quality, volume, musicVolume, fullscreen, vsync, subtitles, language),
                "Настройки сохранены", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->buttonBack = (gcnew System::Windows::Forms::Button());
            this->groupBoxGraphics = (gcnew System::Windows::Forms::GroupBox());
            this->comboBoxResolution = (gcnew System::Windows::Forms::ComboBox());
            this->labelResolution = (gcnew System::Windows::Forms::Label());
            this->checkBoxFullscreen = (gcnew System::Windows::Forms::CheckBox());
            this->groupBoxAudio = (gcnew System::Windows::Forms::GroupBox());
            this->trackBarVolume = (gcnew System::Windows::Forms::TrackBar());
            this->labelVolume = (gcnew System::Windows::Forms::Label());
            this->labelVolumeValue = (gcnew System::Windows::Forms::Label());
            this->buttonSave = (gcnew System::Windows::Forms::Button());
            this->buttonCancel = (gcnew System::Windows::Forms::Button());
            this->panelContainer = (gcnew System::Windows::Forms::Panel());
            this->comboBoxQuality = (gcnew System::Windows::Forms::ComboBox());
            this->labelQuality = (gcnew System::Windows::Forms::Label());
            this->checkBoxVSync = (gcnew System::Windows::Forms::CheckBox());
            this->trackBarMusic = (gcnew System::Windows::Forms::TrackBar());
            this->labelMusic = (gcnew System::Windows::Forms::Label());
            this->labelMusicValue = (gcnew System::Windows::Forms::Label());
            this->checkBoxSubtitles = (gcnew System::Windows::Forms::CheckBox());
            this->comboBoxLanguage = (gcnew System::Windows::Forms::ComboBox());
            this->groupBoxGraphics->SuspendLayout();
            this->groupBoxAudio->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarVolume))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarMusic))->BeginInit();
            this->panelContainer->SuspendLayout();
            this->SuspendLayout();

            // 
            // panelContainer
            // 
            this->panelContainer->BackColor = System::Drawing::Color::Black;
            this->panelContainer->Controls->Add(this->comboBoxLanguage);
            this->panelContainer->Controls->Add(this->checkBoxSubtitles);
            this->panelContainer->Controls->Add(this->groupBoxAudio);
            this->panelContainer->Controls->Add(this->groupBoxGraphics);
            this->panelContainer->Controls->Add(this->buttonBack);
            this->panelContainer->Controls->Add(this->buttonSave);
            this->panelContainer->Controls->Add(this->buttonCancel);
            this->panelContainer->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panelContainer->Location = System::Drawing::Point(0, 0);
            this->panelContainer->Name = L"panelContainer";
            this->panelContainer->Size = System::Drawing::Size(800, 650);
            this->panelContainer->TabIndex = 5;

            // 
            // buttonBack
            // 
            this->buttonBack->Location = System::Drawing::Point(30, 30);
            this->buttonBack->Name = L"buttonBack";
            this->buttonBack->Size = System::Drawing::Size(120, 45);
            this->buttonBack->TabIndex = 0;
            this->buttonBack->Text = L"? Назад";
            this->buttonBack->UseVisualStyleBackColor = false;
            this->buttonBack->BackColor = System::Drawing::Color::FromArgb(50, 50, 50);
            this->buttonBack->ForeColor = System::Drawing::Color::White;
            this->buttonBack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold));
            this->buttonBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonBack->FlatAppearance->BorderSize = 0;
            this->buttonBack->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(70, 70, 70);
            this->buttonBack->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->buttonBack->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonBack->Click += gcnew System::EventHandler(this, &Settings::buttonBack_Click);

            // 
            // groupBoxGraphics (Сдвинуто вправо)
            // 
            this->groupBoxGraphics->Controls->Add(this->checkBoxVSync);
            this->groupBoxGraphics->Controls->Add(this->comboBoxQuality);
            this->groupBoxGraphics->Controls->Add(this->labelQuality);
            this->groupBoxGraphics->Controls->Add(this->checkBoxFullscreen);
            this->groupBoxGraphics->Controls->Add(this->comboBoxResolution);
            this->groupBoxGraphics->Controls->Add(this->labelResolution);
            this->groupBoxGraphics->ForeColor = System::Drawing::Color::White;
            this->groupBoxGraphics->Location = System::Drawing::Point(50, 100);
            this->groupBoxGraphics->Name = L"groupBoxGraphics";
            this->groupBoxGraphics->Size = System::Drawing::Size(320, 220);
            this->groupBoxGraphics->TabIndex = 1;
            this->groupBoxGraphics->TabStop = false;
            this->groupBoxGraphics->Text = L"Графика";
            this->groupBoxGraphics->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);

            // 
            // labelResolution
            // 
            this->labelResolution->ForeColor = System::Drawing::Color::White;
            this->labelResolution->Location = System::Drawing::Point(20, 40);
            this->labelResolution->Name = L"labelResolution";
            this->labelResolution->Size = System::Drawing::Size(100, 25);
            this->labelResolution->TabIndex = 0;
            this->labelResolution->Text = L"Разрешение:";
            this->labelResolution->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

            // 
            // comboBoxResolution
            // 
            this->comboBoxResolution->BackColor = System::Drawing::Color::FromArgb(50, 50, 50);
            this->comboBoxResolution->ForeColor = System::Drawing::Color::White;
            this->comboBoxResolution->FormattingEnabled = true;
            this->comboBoxResolution->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
                L"1920x1080", L"1600x900", L"1366x768", L"1280x720", L"1024x768", L"800x600"
            });
            this->comboBoxResolution->Location = System::Drawing::Point(130, 40);
            this->comboBoxResolution->Name = L"comboBoxResolution";
            this->comboBoxResolution->Size = System::Drawing::Size(160, 33);
            this->comboBoxResolution->TabIndex = 1;
            this->comboBoxResolution->FlatStyle = System::Windows::Forms::FlatStyle::Flat;

            // 
            // checkBoxFullscreen
            // 
            this->checkBoxFullscreen->ForeColor = System::Drawing::Color::White;
            this->checkBoxFullscreen->Location = System::Drawing::Point(20, 160);
            this->checkBoxFullscreen->Name = L"checkBoxFullscreen";
            this->checkBoxFullscreen->Size = System::Drawing::Size(200, 30);
            this->checkBoxFullscreen->TabIndex = 4;
            this->checkBoxFullscreen->Text = L"Полноэкранный режим";
            this->checkBoxFullscreen->UseVisualStyleBackColor = true;

            // 
            // labelQuality
            // 
            this->labelQuality->ForeColor = System::Drawing::Color::White;
            this->labelQuality->Location = System::Drawing::Point(20, 80);
            this->labelQuality->Name = L"labelQuality";
            this->labelQuality->Size = System::Drawing::Size(100, 25);
            this->labelQuality->TabIndex = 2;
            this->labelQuality->Text = L"Качество:";
            this->labelQuality->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

            // 
            // comboBoxQuality
            // 
            this->comboBoxQuality->BackColor = System::Drawing::Color::FromArgb(50, 50, 50);
            this->comboBoxQuality->ForeColor = System::Drawing::Color::White;
            this->comboBoxQuality->FormattingEnabled = true;
            this->comboBoxQuality->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
                L"Очень низкое", L"Низкое", L"Среднее", L"Высокое"
            });
            this->comboBoxQuality->Location = System::Drawing::Point(130, 80);
            this->comboBoxQuality->Name = L"comboBoxQuality";
            this->comboBoxQuality->Size = System::Drawing::Size(160, 33);
            this->comboBoxQuality->TabIndex = 3;
            this->comboBoxQuality->FlatStyle = System::Windows::Forms::FlatStyle::Flat;

            // 
            // checkBoxVSync
            // 
            this->checkBoxVSync->ForeColor = System::Drawing::Color::White;
            this->checkBoxVSync->Location = System::Drawing::Point(20, 120);
            this->checkBoxVSync->Name = L"checkBoxVSync";
            this->checkBoxVSync->Size = System::Drawing::Size(200, 30);
            this->checkBoxVSync->TabIndex = 5;
            this->checkBoxVSync->Text = L"Вертикальная синхронизация";
            this->checkBoxVSync->UseVisualStyleBackColor = true;

            // 
            // groupBoxAudio (Сдвинуто вправо)
            // 
            this->groupBoxAudio->Controls->Add(this->labelMusicValue);
            this->groupBoxAudio->Controls->Add(this->trackBarMusic);
            this->groupBoxAudio->Controls->Add(this->labelMusic);
            this->groupBoxAudio->Controls->Add(this->labelVolumeValue);
            this->groupBoxAudio->Controls->Add(this->trackBarVolume);
            this->groupBoxAudio->Controls->Add(this->labelVolume);
            this->groupBoxAudio->ForeColor = System::Drawing::Color::White;
            this->groupBoxAudio->Location = System::Drawing::Point(400, 100);
            this->groupBoxAudio->Name = L"groupBoxAudio";
            this->groupBoxAudio->Size = System::Drawing::Size(320, 220);
            this->groupBoxAudio->TabIndex = 2;
            this->groupBoxAudio->TabStop = false;
            this->groupBoxAudio->Text = L"Звук";
            this->groupBoxAudio->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);

            // 
            // labelVolume
            // 
            this->labelVolume->ForeColor = System::Drawing::Color::White;
            this->labelVolume->Location = System::Drawing::Point(20, 40);
            this->labelVolume->Name = L"labelVolume";
            this->labelVolume->Size = System::Drawing::Size(100, 25);
            this->labelVolume->TabIndex = 0;
            this->labelVolume->Text = L"Громкость:";
            this->labelVolume->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

            // 
            // trackBarVolume
            // 
            this->trackBarVolume->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->trackBarVolume->Location = System::Drawing::Point(130, 40);
            this->trackBarVolume->Maximum = 100;
            this->trackBarVolume->Name = L"trackBarVolume";
            this->trackBarVolume->Size = System::Drawing::Size(160, 69);
            this->trackBarVolume->TabIndex = 1;
            this->trackBarVolume->TickFrequency = 10;
            this->trackBarVolume->Value = 80;
            this->trackBarVolume->Scroll += gcnew System::EventHandler(this, &Settings::trackBarVolume_Scroll);

            // 
            // labelVolumeValue
            // 
            this->labelVolumeValue->ForeColor = System::Drawing::Color::White;
            this->labelVolumeValue->Location = System::Drawing::Point(130, 70);
            this->labelVolumeValue->Name = L"labelVolumeValue";
            this->labelVolumeValue->Size = System::Drawing::Size(160, 25);
            this->labelVolumeValue->TabIndex = 2;
            this->labelVolumeValue->Text = L"80%";
            this->labelVolumeValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // 
            // labelMusic
            // 
            this->labelMusic->ForeColor = System::Drawing::Color::White;
            this->labelMusic->Location = System::Drawing::Point(20, 120);
            this->labelMusic->Name = L"labelMusic";
            this->labelMusic->Size = System::Drawing::Size(100, 25);
            this->labelMusic->TabIndex = 3;
            this->labelMusic->Text = L"Музыка:";
            this->labelMusic->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

            // 
            // trackBarMusic
            // 
            this->trackBarMusic->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->trackBarMusic->Location = System::Drawing::Point(130, 120);
            this->trackBarMusic->Maximum = 100;
            this->trackBarMusic->Name = L"trackBarMusic";
            this->trackBarMusic->Size = System::Drawing::Size(160, 69);
            this->trackBarMusic->TabIndex = 4;
            this->trackBarMusic->TickFrequency = 10;
            this->trackBarMusic->Value = 70;
            this->trackBarMusic->Scroll += gcnew System::EventHandler(this, &Settings::trackBarMusic_Scroll);

            // 
            // labelMusicValue
            // 
            this->labelMusicValue->ForeColor = System::Drawing::Color::White;
            this->labelMusicValue->Location = System::Drawing::Point(130, 150);
            this->labelMusicValue->Name = L"labelMusicValue";
            this->labelMusicValue->Size = System::Drawing::Size(160, 25);
            this->labelMusicValue->TabIndex = 5;
            this->labelMusicValue->Text = L"70%";
            this->labelMusicValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // 
            // checkBoxSubtitles
            // 
            this->checkBoxSubtitles->ForeColor = System::Drawing::Color::White;
            this->checkBoxSubtitles->Location = System::Drawing::Point(50, 350);
            this->checkBoxSubtitles->Name = L"checkBoxSubtitles";
            this->checkBoxSubtitles->Size = System::Drawing::Size(250, 30);
            this->checkBoxSubtitles->TabIndex = 6;
            this->checkBoxSubtitles->Text = L"Показывать субтитры";
            this->checkBoxSubtitles->UseVisualStyleBackColor = true;

            // 
            // comboBoxLanguage
            // 
            this->comboBoxLanguage->BackColor = System::Drawing::Color::FromArgb(50, 50, 50);
            this->comboBoxLanguage->ForeColor = System::Drawing::Color::White;
            this->comboBoxLanguage->FormattingEnabled = true;
            this->comboBoxLanguage->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
                L"Русский", L"English", L"Espa?ol"
            });
            this->comboBoxLanguage->Location = System::Drawing::Point(400, 350);
            this->comboBoxLanguage->Name = L"comboBoxLanguage";
            this->comboBoxLanguage->Size = System::Drawing::Size(160, 33);
            this->comboBoxLanguage->TabIndex = 7;
            this->comboBoxLanguage->FlatStyle = System::Windows::Forms::FlatStyle::Flat;

            // 
            // buttonSave
            // 
            this->buttonSave->Location = System::Drawing::Point(400, 450);
            this->buttonSave->Name = L"buttonSave";
            this->buttonSave->Size = System::Drawing::Size(150, 50);
            this->buttonSave->TabIndex = 3;
            this->buttonSave->Text = L"Сохранить";
            this->buttonSave->UseVisualStyleBackColor = false;
            this->buttonSave->BackColor = System::Drawing::Color::FromArgb(0, 120, 215);
            this->buttonSave->ForeColor = System::Drawing::Color::White;
            this->buttonSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold));
            this->buttonSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonSave->FlatAppearance->BorderSize = 0;
            this->buttonSave->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(0, 150, 255);
            this->buttonSave->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(0, 90, 180);
            this->buttonSave->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonSave->Click += gcnew System::EventHandler(this, &Settings::buttonSave_Click);

            // 
            // buttonCancel
            // 
            this->buttonCancel->Location = System::Drawing::Point(570, 450);
            this->buttonCancel->Name = L"buttonCancel";
            this->buttonCancel->Size = System::Drawing::Size(150, 50);
            this->buttonCancel->TabIndex = 4;
            this->buttonCancel->Text = L"Отмена";
            this->buttonCancel->UseVisualStyleBackColor = false;
            this->buttonCancel->BackColor = System::Drawing::Color::FromArgb(80, 80, 80);
            this->buttonCancel->ForeColor = System::Drawing::Color::White;
            this->buttonCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold));
            this->buttonCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonCancel->FlatAppearance->BorderSize = 0;
            this->buttonCancel->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(100, 100, 100);
            this->buttonCancel->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(60, 60, 60);
            this->buttonCancel->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonCancel->Click += gcnew System::EventHandler(this, &Settings::buttonCancel_Click);

            // 
            // Settings
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Black;
            this->ClientSize = System::Drawing::Size(800, 650);
            this->Controls->Add(this->panelContainer);
            this->Name = L"Settings";
            this->Text = L"Настройки";
            this->ForeColor = System::Drawing::Color::White;
            this->groupBoxGraphics->ResumeLayout(false);
            this->groupBoxGraphics->PerformLayout();
            this->groupBoxAudio->ResumeLayout(false);
            this->groupBoxAudio->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarVolume))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarMusic))->EndInit();
            this->panelContainer->ResumeLayout(false);
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }

        System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SaveSettings(); // Сохраняем настройки
            this->Close();
        }

        System::Void buttonCancel_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }

        System::Void trackBarVolume_Scroll(System::Object^ sender, System::EventArgs^ e)
        {
            if (trackBarVolume != nullptr && labelVolumeValue != nullptr)
            {
                this->labelVolumeValue->Text = trackBarVolume->Value.ToString() + "%";
                // Здесь можно добавить код для изменения громкости в реальном времени
            }
        }

        System::Void trackBarMusic_Scroll(System::Object^ sender, System::EventArgs^ e)
        {
            if (trackBarMusic != nullptr && labelMusicValue != nullptr)
            {
                this->labelMusicValue->Text = trackBarMusic->Value.ToString() + "%";
                // Здесь можно добавить код для изменения громкости музыки
            }
        }
    };
}