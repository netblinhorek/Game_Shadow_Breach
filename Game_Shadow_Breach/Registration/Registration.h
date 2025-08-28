#pragma once

#include "../Utils/CsvStorage.h"
#include "../Main.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Registration
	/// </summary>
	public ref class Registration : public System::Windows::Forms::Form
	{
	public:
		Registration(void)
		{
			InitializeComponent();
			LoadBackgroundImage();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Registration()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::Button^ buttonExit;
		System::Windows::Forms::TextBox^ textPlayerName;
		System::Windows::Forms::Button^ buttonStart;

	private:
		void LoadBackgroundImage()
		{
			try
			{
				array<String^>^ possiblePaths = {
					"регистрация.png" 
				};

				bool imageLoaded = false;
				for each (String ^ path in possiblePaths)
				{
					if (System::IO::File::Exists(path))
					{
						pictureBox1->Image = Image::FromFile(path);
						pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
						pictureBox1->Dock = DockStyle::Fill;
						imageLoaded = true;
						break;
					}
				}

				if (!imageLoaded)
				{
					pictureBox1->BackColor = Color::LightGray;
					MessageBox::Show("Фоновая картинка не найдена!", "Ошибка",
						MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}
			catch (Exception^ ex)
			{
				pictureBox1->BackColor = Color::LightGray;
				MessageBox::Show("Ошибка загрузки фонового изображения: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->buttonExit = (gcnew System::Windows::Forms::Button());
			this->textPlayerName = (gcnew System::Windows::Forms::TextBox());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// pictureBox1 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(800, 600);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;

			// buttonExit 
			this->buttonExit->Location = System::Drawing::Point(10, 10);
			this->buttonExit->Name = L"buttonExit";
			this->buttonExit->Size = System::Drawing::Size(100, 40);
			this->buttonExit->TabIndex = 1;
			this->buttonExit->Text = L"Выход";
			this->buttonExit->UseVisualStyleBackColor = true;
			this->buttonExit->BackColor = System::Drawing::Color::LightGray;
			this->buttonExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
			this->buttonExit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonExit->Click += gcnew System::EventHandler(this, &Registration::buttonExit_Click);

			// textPlayerName
			this->textPlayerName->Location = System::Drawing::Point(250, 450);
			this->textPlayerName->Size = System::Drawing::Size(300, 22);
			this->textPlayerName->PlaceholderText = L"Введите имя игрока";

			// buttonStart
			this->buttonStart->Location = System::Drawing::Point(560, 445);
			this->buttonStart->Size = System::Drawing::Size(120, 32);
			this->buttonStart->Text = L"Начать";
			this->buttonStart->Click += gcnew System::EventHandler(this, &Registration::buttonStart_Click);

			// Registration
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 600);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;

			
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->buttonExit);
			this->Controls->Add(this->textPlayerName);
			this->Controls->Add(this->buttonStart);

			this->Name = L"Registration";
			this->Text = L"Регистрация";
			this->StartPosition = FormStartPosition::CenterScreen;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
		}

	#pragma endregion

	private:
		System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (MessageBox::Show("Вы уверены, что хотите выйти?", "Подтверждение",
				MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
			{
				this->Close();
			}
		}

		System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e)
		{
			String^ name = textPlayerName->Text;
			if (String::IsNullOrWhiteSpace(name))
			{
				MessageBox::Show("Введите имя игрока", "Внимание");
				return;
			}

			
			array<String^>^ row = { name, DateTime::Now.ToString("u"), "0" };
			CsvStorage::AppendRow(row);

			
			this->Hide();
			Main^ mainForm = gcnew Main();
			mainForm->Show();
		}
	};
}