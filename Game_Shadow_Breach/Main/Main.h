#pragma once
#include "Play_game.h"
#include "Settings.h"
#include "Shop.h"
namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();
			LoadBackgroundImage(); // Загружаем изображение при создании формы
		}

	protected:
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::Button^ button2;
		System::Windows::Forms::Button^ button3;
		System::Windows::Forms::Button^ button4;
		System::Windows::Forms::PictureBox^ pictureBox1;

	private:
		System::ComponentModel::Container^ components;

		// Метод для загрузки фонового изображения
		void LoadBackgroundImage()
		{
			try
			{
				String^ imagePath = "C:\\Users\\redmi\\Pictures\\Screenshots\\Снимок экрана 2025-08-15 000232.png";

				// Проверяем существование файла
				if (System::IO::File::Exists(imagePath))
				{
					// Загружаем изображение в PictureBox
					pictureBox1->Image = Image::FromFile(imagePath);
					pictureBox1->SizeMode = PictureBoxSizeMode::Zoom; // Масштабируем по размеру
				}
				else
				{
					MessageBox::Show("Файл изображения не найден: " + imagePath,
						"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка загрузки изображения: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button()); 
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(85, 350);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(220, 70);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Играть";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->BackColor = System::Drawing::Color::Black;
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold));
			this->button1->FlatAppearance->BorderSize = 1;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(68, 68, 68);
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(34, 34, 34);
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(17, 17, 17);
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Click += gcnew System::EventHandler(this, &Main::button1_Click_1);


			// 
			// button2  
			// 
			this->button2->Location = System::Drawing::Point(85, 415); 
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(220, 70);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Настройки";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->BackColor = System::Drawing::Color::Black;
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold));
			this->button2->FlatAppearance->BorderSize = 1;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(68, 68, 68);
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(34, 34, 34);
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(17, 17, 17);
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Click += gcnew System::EventHandler(this, &Main::button2_Click_1);

			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(85, 480);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(220, 70);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Магазин";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->BackColor = System::Drawing::Color::Black;
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold));
			this->button3->FlatAppearance->BorderSize = 1;
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(68, 68, 68);
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(34, 34, 34);
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(17, 17, 17);
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->Click += gcnew System::EventHandler(this, &Main::button3_Click_1);

			// 
			// button4
			// 
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button4->Location = System::Drawing::Point(85, 545);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(220, 70);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Выход";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->BackColor = System::Drawing::Color::Black;
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, FontStyle::Bold));
			this->button4->FlatAppearance->BorderSize = 1;
			this->button4->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(68, 68, 68);
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(34, 34, 34);
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(17, 17, 17);
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->Click += gcnew System::EventHandler(this, &Main::button4_Click_1);

			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill; // Заполняет всю форму
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1359, 793);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;

			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1359, 793);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Main";
			this->Text = L"Главная - Shadow Breach";
			this->StartPosition = FormStartPosition::CenterScreen;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e)
		{
			try
			{
				CppCLRWinFormsProject::Play_game^ play_game = gcnew CppCLRWinFormsProject::Play_game();
				this->Hide();
				play_game->ShowDialog();
				this->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка при переходе на игровую страницу: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e)
		{
			try
			{
				CppCLRWinFormsProject::Settings^ settings = gcnew CppCLRWinFormsProject::Settings();
				settings->ShowDialog(); // Просто показываем диалог, не скрывая главную форму
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка при переходе на страницу настроек: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		System::Void button3_Click_1(System::Object^ sender, System::EventArgs^ e)
		{
			try
			{
				CppCLRWinFormsProject::Shop^ shop = gcnew CppCLRWinFormsProject::Shop();
				this->Hide();
				shop->ShowDialog();
				this->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка при переходе на страницу настроек: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		System::Void button4_Click_1(System::Object^ sender, System::EventArgs^ e)
		{
			// Используем полное квалифицированное имя для DialogResult
			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Вы уверены, что хотите выйти из программы?",
				"Подтверждение выхода",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Question
			);

			// Используем полное квалифицированное имя для сравнения
			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				Application::Exit();
			}
		}
	};
}