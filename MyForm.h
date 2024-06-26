﻿/*
* Проект "Матрица смежности графа"
* Разработчик: Сапрыкин Семён
* Дата: 2024 год
* Язык программирования: C++/CLI
* Среда разработки: Visual Studio 2022
* Описание: Программа позволяет создавать графы с помощью матрицы смежности.
* Пользователь может добавлять вершины и ребра между ними.
* Программа отображает графическое представление графа и матрицу смежности.
* Приложение позволяет создавать графы с количеством вершин от 1 до 20.
* Приложение позволяет создавать ребра между вершинами.
*/


#pragma once

#include <cmath>
#include <cstdlib>
#include <ctime>

namespace WinFormsGraph {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            srand(time(0));

            // Инициализирование выбранную вершину значением -1
            selectedVertex = -1;

            // Добавить обработчик событий для нажатия кнопки "Добавить точку"
            this->addDot->Click += gcnew System::EventHandler(this, &MyForm::addDot_Click);
            this->graphBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::graphBox_MouseClick);
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Button^ addDot;
    private: System::Windows::Forms::PictureBox^ graphBox;
    private: System::Windows::Forms::TextBox^ amountOfDots;
    private: System::Windows::Forms::Button^ buttonCreate;
    private: System::Windows::Forms::TextBox^ boxLast_1;
    private: System::Windows::Forms::TextBox^ boxLast_2;
    private: System::Windows::Forms::RichTextBox^ richTextBox1;
    private: System::Windows::Forms::RichTextBox^ richTextBox2;
    private: System::Windows::Forms::RichTextBox^ matrixBox;

           System::ComponentModel::Container^ components;
           array<array<int>^>^ adjacencyMatrix;
           array<Point>^ points;
           int selectedVertex;
           int lastVertex1;
    private: System::Windows::Forms::RichTextBox^ richTextBox3;
           int lastVertex2;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->addDot = (gcnew System::Windows::Forms::Button());
               this->graphBox = (gcnew System::Windows::Forms::PictureBox());
               this->amountOfDots = (gcnew System::Windows::Forms::TextBox());
               this->buttonCreate = (gcnew System::Windows::Forms::Button());
               this->boxLast_1 = (gcnew System::Windows::Forms::TextBox());
               this->boxLast_2 = (gcnew System::Windows::Forms::TextBox());
               this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
               this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
               this->matrixBox = (gcnew System::Windows::Forms::RichTextBox());
               this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graphBox))->BeginInit();
               this->SuspendLayout();
               // 
               // label1
               // 
               this->label1->AutoSize = true;
               this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
               this->label1->Location = System::Drawing::Point(28, 9);
               this->label1->Name = L"label1";
               this->label1->Size = System::Drawing::Size(430, 38);
               this->label1->TabIndex = 0;
               this->label1->Text = L"Матрица смежности графа";
               // 
               // addDot
               // 
               this->addDot->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
               this->addDot->Location = System::Drawing::Point(19, 481);
               this->addDot->Name = L"addDot";
               this->addDot->Size = System::Drawing::Size(268, 39);
               this->addDot->TabIndex = 2;
               this->addDot->Text = L"Добавить вершину";
               this->addDot->UseVisualStyleBackColor = true;
               // 
               // graphBox
               // 
               this->graphBox->Location = System::Drawing::Point(323, 50);
               this->graphBox->Name = L"graphBox";
               this->graphBox->Size = System::Drawing::Size(440, 425);
               this->graphBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
               this->graphBox->TabIndex = 3;
               this->graphBox->TabStop = false;
               // 
               // amountOfDots
               // 
               this->amountOfDots->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
               this->amountOfDots->Location = System::Drawing::Point(783, 72);
               this->amountOfDots->Name = L"amountOfDots";
               this->amountOfDots->Size = System::Drawing::Size(140, 44);
               this->amountOfDots->TabIndex = 6;
               // 
               // buttonCreate
               // 
               this->buttonCreate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
               this->buttonCreate->Location = System::Drawing::Point(783, 110);
               this->buttonCreate->Name = L"buttonCreate";
               this->buttonCreate->Size = System::Drawing::Size(140, 33);
               this->buttonCreate->TabIndex = 7;
               this->buttonCreate->Text = L"Построить";
               this->buttonCreate->UseVisualStyleBackColor = true;
               this->buttonCreate->Click += gcnew System::EventHandler(this, &MyForm::buttonCreate_Click);
               // 
               // boxLast_1
               // 
               this->boxLast_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
               this->boxLast_1->Location = System::Drawing::Point(783, 426);
               this->boxLast_1->Multiline = true;
               this->boxLast_1->Name = L"boxLast_1";
               this->boxLast_1->Size = System::Drawing::Size(50, 34);
               this->boxLast_1->TabIndex = 8;
               // 
               // boxLast_2
               // 
               this->boxLast_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
               this->boxLast_2->Location = System::Drawing::Point(865, 426);
               this->boxLast_2->Multiline = true;
               this->boxLast_2->Name = L"boxLast_2";
               this->boxLast_2->Size = System::Drawing::Size(58, 34);
               this->boxLast_2->TabIndex = 9;
               // 
               // richTextBox1
               // 
               this->richTextBox1->BackColor = System::Drawing::Color::White;
               this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
               this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
               this->richTextBox1->Location = System::Drawing::Point(323, 481);
               this->richTextBox1->Name = L"richTextBox1";
               this->richTextBox1->ReadOnly = true;
               this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
               this->richTextBox1->Size = System::Drawing::Size(523, 63);
               this->richTextBox1->TabIndex = 10;
               this->richTextBox1->Text = L"Для добавления ребра щёлкните мышью вершины, которые оно должно соединить";
               // 
               // richTextBox2
               // 
               this->richTextBox2->BackColor = System::Drawing::Color::White;
               this->richTextBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
               this->richTextBox2->Cursor = System::Windows::Forms::Cursors::Default;
               this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->richTextBox2->Location = System::Drawing::Point(780, 9);
               this->richTextBox2->Name = L"richTextBox2";
               this->richTextBox2->ReadOnly = true;
               this->richTextBox2->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
               this->richTextBox2->Size = System::Drawing::Size(178, 95);
               this->richTextBox2->TabIndex = 11;
               this->richTextBox2->Text = L"Число вершин графа (n)";
               // 
               // matrixBox
               // 
               this->matrixBox->Location = System::Drawing::Point(19, 50);
               this->matrixBox->Name = L"matrixBox";
               this->matrixBox->Size = System::Drawing::Size(268, 425);
               this->matrixBox->TabIndex = 12;
               this->matrixBox->Text = L"";
               // 
               // richTextBox3
               // 
               this->richTextBox3->BackColor = System::Drawing::Color::White;
               this->richTextBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
               this->richTextBox3->Cursor = System::Windows::Forms::Cursors::Default;
               this->richTextBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->richTextBox3->Location = System::Drawing::Point(780, 373);
               this->richTextBox3->Name = L"richTextBox3";
               this->richTextBox3->ReadOnly = true;
               this->richTextBox3->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
               this->richTextBox3->Size = System::Drawing::Size(143, 47);
               this->richTextBox3->TabIndex = 13;
               this->richTextBox3->Text = L"Соединенные точки:";
               // 
               // MyForm
               // 
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
               this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
               this->ClientSize = System::Drawing::Size(935, 546);
               this->Controls->Add(this->richTextBox3);
               this->Controls->Add(this->amountOfDots);
               this->Controls->Add(this->addDot);
               this->Controls->Add(this->matrixBox);
               this->Controls->Add(this->richTextBox2);
               this->Controls->Add(this->richTextBox1);
               this->Controls->Add(this->boxLast_2);
               this->Controls->Add(this->boxLast_1);
               this->Controls->Add(this->buttonCreate);
               this->Controls->Add(this->graphBox);
               this->Controls->Add(this->label1);
               this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
               this->ForeColor = System::Drawing::SystemColors::Desktop;
               this->Name = L"MyForm";
               this->Text = L"Матрица смежности графа";
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graphBox))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    private:
        void buttonCreate_Click(System::Object^ sender, System::EventArgs^ e) {
            if (String::IsNullOrEmpty(amountOfDots->Text)) {
                MessageBox::Show("Пожалуйста, введите количество вершин.");
                return;
            }

            int n = Convert::ToInt32(amountOfDots->Text);
            if (n < 1 || n > 20) {
                MessageBox::Show("Введите число вершин в пределах от 1 до 20.");
                return;
            }
            GenerateGraph(n);
        }

        void addDot_Click(System::Object^ sender, System::EventArgs^ e) {
            // Увеличение количества вершин
            int n;
            if (amountOfDots->Text == "") {
                n = 0;
            }
            else {
                n = Convert::ToInt32(amountOfDots->Text);
            }
            if (n < 20) { // Ограничение количества вершин до 20
                n++;
                amountOfDots->Text = n.ToString();
                GenerateGraph(n);
            }
            else {
                MessageBox::Show("Максимальное количество вершин - 20.");
            }
        }

        void GenerateGraph(int n) {
            // Сгенерировать матрицу смежности
            adjacencyMatrix = gcnew array<array<int>^>(n);
            for (int i = 0; i < n; i++) {
                adjacencyMatrix[i] = gcnew array<int>(n);
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        adjacencyMatrix[i][j] = rand() % 2;
                    }
                    else {
                        adjacencyMatrix[i][j] = 0;
                    }
                }
            }

            // Создание симметричной матрицы 
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                }
            }

            // Отображение матрицы смежности с выделенными элементами
            matrixBox->Clear();
            matrixBox->SelectionStart = matrixBox->Text->Length;
            matrixBox->SelectionLength = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adjacencyMatrix[i][j] == 1) {
                        matrixBox->SelectionColor = Color::Red;
                    }
                    else {
                        matrixBox->SelectionColor = Color::Black;
                    }
                    matrixBox->AppendText(adjacencyMatrix[i][j].ToString() + " ");
                }
                matrixBox->AppendText("\r\n");
            }

            // Отображение графика
            DrawGraph(adjacencyMatrix, n);
        }

        void DrawGraph(array<array<int>^>^ matrix, int n) {
            Graphics^ g = graphBox->CreateGraphics();
            g->Clear(SystemColors::ButtonHighlight);
            Pen^ pen = gcnew Pen(Color::Green);
            Brush^ brush = gcnew SolidBrush(Color::Yellow);
            Brush^ textBrush = gcnew SolidBrush(Color::Black);
            int R = 200;
            Point center(graphBox->Width / 2, graphBox->Height / 2);
            points = gcnew array<Point>(n);

            for (int i = 0; i < n; i++) {
                double angle = 2 * Math::PI * i / n;
                int x = center.X + (int)(R * Math::Cos(angle));
                int y = center.Y + (int)(R * Math::Sin(angle));
                points[i] = Point(x, y);
                g->FillEllipse(brush, x - 10, y - 10, 20, 20); // Заливка круг желтым цветом
                g->DrawEllipse(pen, x - 10, y - 10, 20, 20); // Нарисуйте границу круга
                g->DrawString((i + 1).ToString(), gcnew System::Drawing::Font("Microsoft Sans Serif", 12), textBrush, x + 10, y - 10); // Нарисуйте число
            }

            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (matrix[i][j] == 1) {
                        g->DrawLine(pen, points[i], points[j]);
                    }
                }
            }
        }

        void graphBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
            if (points == nullptr || points->Length == 0)
                return;

            // Определите, был ли нажат щелчок по вершине
            int clickedVertex = -1;
            for (int i = 0; i < points->Length; i++) {
                if (Math::Pow(e->X - points[i].X, 2) + Math::Pow(e->Y - points[i].Y, 2) <= 100) { // 100 - это пороговый радиус для щелчка по вершине
                    clickedVertex = i;
                    break;
                }
            }

            if (clickedVertex == -1)
                return; // Ни одна вершина не была нажата

            if (selectedVertex == -1) {
                selectedVertex = clickedVertex; // Первая выбранная вершина
            }
            else {
                // Проверка, не выбрана ли одна и та же вершина
                if (selectedVertex != clickedVertex) {
                    // Добавление ребро между выбранной вершиной и clickedVertex
                    adjacencyMatrix[selectedVertex][clickedVertex] = 1;
                    adjacencyMatrix[clickedVertex][selectedVertex] = 1;

                    // Обновление отображения графика
                    Graphics^ g = graphBox->CreateGraphics();
                    Pen^ pen = gcnew Pen(Color::Green);
                    g->DrawLine(pen, points[selectedVertex], points[clickedVertex]);

                    // Сохраните последние соединенные вершины
                    lastVertex1 = selectedVertex;
                    lastVertex2 = clickedVertex;

                    // Обновление boxLast_1 и boxLast_2
                    boxLast_1->Text = (lastVertex1 + 1).ToString();
                    boxLast_2->Text = (lastVertex2 + 1).ToString();

                    // Сбросить выбранный параметр
                    selectedVertex = -1;

                    // Обновление отображения матрицы смежности
                    matrixBox->Clear();
                    matrixBox->SelectionStart = matrixBox->Text->Length;
                    matrixBox->SelectionLength = 0;
                    for (int i = 0; i < adjacencyMatrix->Length; i++) {
                        for (int j = 0; j < adjacencyMatrix[i]->Length; j++) {
                            if (adjacencyMatrix[i][j] == 1) {
                                matrixBox->SelectionColor = Color::Red;
                            }
                            else {
                                matrixBox->SelectionColor = Color::Black;
                            }
                            matrixBox->AppendText(adjacencyMatrix[i][j].ToString() + " ");
                        }
                        matrixBox->AppendText("\r\n");
                    }
                }
                else {
                    // Сброс выбранной вершины при повторном нажатии на ту же вершину
                    selectedVertex = -1;
                }
            }
        }
    };
}
