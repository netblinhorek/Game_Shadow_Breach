#pragma once

#include "Main.h"
namespace CppCLRWinFormsProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for Play_game
    /// </summary>
    public ref class Play_game : public System::Windows::Forms::Form
    {
    public:
        Play_game(void)
        {
            InitializeComponent();
            InitializePanels();
            LoadBackgroundImage();
            HideAllPanels(); // Скрыть все панели при запуске
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~Play_game()
        {
            if (components)
            {
                delete components;
            }
        }
    private:
        System::Windows::Forms::Button^ buttonExit;
        System::Windows::Forms::Button^ buttonStatus;
        System::Windows::Forms::Button^ buttonBackpack;
        System::Windows::Forms::PictureBox^ pictureBox1;
        System::Windows::Forms::Panel^ panelStatus;
        System::Windows::Forms::Panel^ panelBackpack;
        System::Windows::Forms::Button^ buttonCloseStatus;
        System::Windows::Forms::Button^ buttonCloseBackpack;

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container^ components;

        void LoadBackgroundImage()
        {
            try
            {
                String^ imagePath = "поле.png";
                if (System::IO::File::Exists(imagePath))
                {
                    pictureBox1->Image = Image::FromFile(imagePath);
                    pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
                }
                else
                {
                    String^ alternativePath = "../../Player_game/поле.png";
                    if (System::IO::File::Exists(alternativePath))
                    {
                        pictureBox1->Image = Image::FromFile(alternativePath);
                        pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
                    }
                    else
                    {
                        pictureBox1->BackColor = Color::LightGray;
                    }
                }
            }
            catch (Exception^ ex)
            {
                pictureBox1->BackColor = Color::LightGray;
            }
        }

        void InitializePanels()
        {
            // Панель состояния персонажа
            panelStatus = gcnew Panel();
            panelStatus->Size = System::Drawing::Size(200, 150);
            panelStatus->Location = System::Drawing::Point(750, 50);
            panelStatus->BackColor = Color::LightGray;
            panelStatus->BorderStyle = BorderStyle::FixedSingle;
            panelStatus->Visible = false;

            buttonCloseStatus = gcnew Button();
            buttonCloseStatus->Text = "X";
            buttonCloseStatus->Size = System::Drawing::Size(25, 25);
            buttonCloseStatus->Location = System::Drawing::Point(panelStatus->Width - 30, 5);
            buttonCloseStatus->BackColor = Color::LightCoral;
            buttonCloseStatus->ForeColor = Color::White;
            buttonCloseStatus->Click += gcnew EventHandler(this, &Play_game::buttonCloseStatus_Click);

            Label^ labelStatus = gcnew Label();
            labelStatus->Text = "СОСТОЯНИЕ";
            labelStatus->Location = System::Drawing::Point(10, 10);
            labelStatus->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Bold);
            labelStatus->AutoSize = true;

            Label^ labelHealth = gcnew Label();
            labelHealth->Text = "Здоровье: 100%";
            labelHealth->Location = System::Drawing::Point(20, 50);
            labelHealth->AutoSize = true;

            Label^ labelMana = gcnew Label();
            labelMana->Text = "Мана: 100%";
            labelMana->Location = System::Drawing::Point(20, 80);
            labelMana->AutoSize = true;

            panelStatus->Controls->Add(buttonCloseStatus);
            panelStatus->Controls->Add(labelStatus);
            panelStatus->Controls->Add(labelHealth);
            panelStatus->Controls->Add(labelMana);

            // Панель рюкзака
            panelBackpack = gcnew Panel();
            panelBackpack->Size = System::Drawing::Size(200, 150);
            panelBackpack->Location = System::Drawing::Point(1100, 100);
            panelBackpack->BackColor = Color::LightGray;
            panelBackpack->BorderStyle = BorderStyle::FixedSingle;
            panelBackpack->Visible = false;

            buttonCloseBackpack = gcnew Button();
            buttonCloseBackpack->Text = "X";
            buttonCloseBackpack->Size = System::Drawing::Size(25, 25);
            buttonCloseBackpack->Location = System::Drawing::Point(panelBackpack->Width - 30, 5);
            buttonCloseBackpack->BackColor = Color::LightCoral;
            buttonCloseBackpack->ForeColor = Color::White;
            buttonCloseBackpack->Click += gcnew EventHandler(this, &Play_game::buttonCloseBackpack_Click);

            Label^ labelBackpack = gcnew Label();
            labelBackpack->Text = "РЮКЗАК";
            labelBackpack->Location = System::Drawing::Point(10, 10);
            labelBackpack->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Bold);
            labelBackpack->AutoSize = true;

            ListBox^ listItems = gcnew ListBox();
            listItems->Location = System::Drawing::Point(20, 40);
            listItems->Size = System::Drawing::Size(160, 100);
            listItems->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9);
            listItems->Items->Add("Меч");
            listItems->Items->Add("Шит");
            listItems->Items->Add("Зелье здоровья");
            listItems->Items->Add("Карта");

            panelBackpack->Controls->Add(buttonCloseBackpack);
            panelBackpack->Controls->Add(labelBackpack);
            panelBackpack->Controls->Add(listItems);

            // Добавляем панели на форму
            this->Controls->Add(panelStatus);
            this->Controls->Add(panelBackpack);
        }

        void HideAllPanels()
        {
            panelStatus->Visible = false;
            panelBackpack->Visible = false;
        }

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            this->buttonExit = (gcnew System::Windows::Forms::Button());
            this->buttonStatus = (gcnew System::Windows::Forms::Button());
            this->buttonBackpack = (gcnew System::Windows::Forms::Button());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->SuspendLayout();

            // buttonExit (завершить) - ПРАВЫЙ НИЖНИЙ УГОЛ
            this->buttonExit->Location = System::Drawing::Point(5, 5);
            this->buttonExit->Name = L"buttonExit";
            this->buttonExit->Size = System::Drawing::Size(150, 75);
            this->buttonExit->TabIndex = 0;
            this->buttonExit->Text = L"завершить";
            this->buttonExit->UseVisualStyleBackColor = true;
            this->buttonExit->BackColor = System::Drawing::Color::LightGray;
            this->buttonExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
            this->buttonExit->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonExit->Click += gcnew System::EventHandler(this, &Play_game::buttonExit_Click);

            // buttonStatus (состояние) - ЛЕВЫЙ ВЕРХНИЙ УГОЛ
            this->buttonStatus->Location = System::Drawing::Point(1150, 5);
            this->buttonStatus->Name = L"buttonStatus";
            this->buttonStatus->Size = System::Drawing::Size(150, 75);
            this->buttonStatus->TabIndex = 1;
            this->buttonStatus->Text = L"состояние";
            this->buttonStatus->UseVisualStyleBackColor = true;
            this->buttonStatus->BackColor = System::Drawing::Color::LightGray;
            this->buttonStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
            this->buttonStatus->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonStatus->Click += gcnew System::EventHandler(this, &Play_game::buttonStatus_Click);

            // buttonBackpack (рюкзак) - ПРАВЫЙ ВЕРХНИЙ УГОЛ
            this->buttonBackpack->Location = System::Drawing::Point(1150, 720);
            this->buttonBackpack->Name = L"buttonBackpack";
            this->buttonBackpack->Size = System::Drawing::Size(150, 75);
            this->buttonBackpack->TabIndex = 3;
            this->buttonBackpack->Text = L"рюкзак";
            this->buttonBackpack->UseVisualStyleBackColor = true;
            this->buttonBackpack->BackColor = System::Drawing::Color::LightGray;
            this->buttonBackpack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
            this->buttonBackpack->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonBackpack->Click += gcnew System::EventHandler(this, &Play_game::buttonBackpack_Click);

            // pictureBox1 - УБИРАЕМ DockStyle::Fill!
            this->pictureBox1->Location = System::Drawing::Point(0, 0);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(1300, 800);
            this->pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
            this->pictureBox1->TabIndex = 4;
            this->pictureBox1->TabStop = false;

            // Play_game
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1300, 800);

            // ВАЖНО: Правильный порядок добавления - сначала кнопки, потом pictureBox
            this->Controls->Add(this->buttonExit);
            this->Controls->Add(this->buttonStatus);
            this->Controls->Add(this->buttonBackpack);
            this->Controls->Add(this->pictureBox1);

            this->Name = L"Play_game";
            this->Text = L"Играть";
            this->StartPosition = FormStartPosition::CenterScreen;
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (MessageBox::Show("Вы уверены, что хотите выйти из игры?", "Подтверждение",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                this->Close();
            }
        }

        System::Void buttonStatus_Click(System::Object^ sender, System::EventArgs^ e)
        {
            HideAllPanels();
            panelStatus->Visible = true;
            panelStatus->BringToFront();
        }

        System::Void buttonBackpack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            HideAllPanels();
            panelBackpack->Visible = true;
            panelBackpack->BringToFront();
        }

        System::Void buttonCloseStatus_Click(System::Object^ sender, System::EventArgs^ e)
        {
            panelStatus->Visible = false;
        }

        System::Void buttonCloseBackpack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            panelBackpack->Visible = false;
        }
    };
}