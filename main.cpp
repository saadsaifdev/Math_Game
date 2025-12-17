#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/* =======================
   ENUMS
======================= */
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

/* =======================
   ANSI COLORS (macOS)
======================= */
void SetGreen()  { cout << "\033[1;32m"; }
void SetRed()    { cout << "\033[1;31m"; }
void ResetColor(){ cout << "\033[0m"; }

/* =======================
   UTILS
======================= */
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case Add:  return "+";
    case Sub:  return "-";
    case Mult: return "x";
    case Div:  return "/";
    default:   return "?";
    }
}

enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

string GetQuestionLevelText(enQuestionsLevel Level)
{
    string Levels[] = { "Easy", "Medium", "Hard", "Mixed" };
    return Levels[Level - 1];
}

/* =======================
   CALCULATOR
======================= */
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case Add:  return Number1 + Number2;
    case Sub:  return Number1 - Number2;
    case Mult: return Number1 * Number2;
    case Div:  return (Number2 != 0) ? Number1 / Number2 : 0;
    default:   return 0;
    }
}

/* =======================
   STRUCTS
======================= */
struct stQuestion
{
    int Number1;
    int Number2;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer;
};

struct stQuiz
{
    stQuestion Questions[100];
    short NumberOfQuestions;
    enQuestionsLevel Level;
    enOperationType OpType;
    short RightAnswers = 0;
    short WrongAnswers = 0;
};

/* =======================
   QUESTION GENERATOR
======================= */
stQuestion GenerateQuestion(enQuestionsLevel Level, enOperationType OpType)
{
    stQuestion Q;

    if (Level == Mix)
        Level = (enQuestionsLevel)RandomNumber(1, 3);

    if (OpType == MixOp)
        OpType = GetRandomOperationType();

    Q.QuestionLevel = Level;
    Q.OperationType = OpType;

    switch (Level)
    {
    case EasyLevel:
        Q.Number1 = RandomNumber(1, 10);
        Q.Number2 = RandomNumber(1, 10);
        break;

    case MedLevel:
        Q.Number1 = RandomNumber(10, 50);
        Q.Number2 = RandomNumber(10, 50);
        break;

    case HardLevel:
        Q.Number1 = RandomNumber(50, 100);
        Q.Number2 = RandomNumber(50, 100);
        break;

    default:
        break;
    }

    Q.CorrectAnswer = SimpleCalculator(Q.Number1, Q.Number2, Q.OperationType);
    return Q;
}

/* =======================
   ASK QUESTIONS
======================= */
void AskQuestions(stQuiz& Quiz)
{
    for (short i = 0; i < Quiz.NumberOfQuestions; i++)
    {
        cout << "\nQuestion [" << i + 1 << "/" << Quiz.NumberOfQuestions << "]\n";
        cout << Quiz.Questions[i].Number1 << " "
             << GetOpTypeSymbol(Quiz.Questions[i].OperationType) << " "
             << Quiz.Questions[i].Number2 << " = ";

        int Answer;
        cin >> Answer;

        if (Answer == Quiz.Questions[i].CorrectAnswer)
        {
            SetGreen();
            cout << "Correct!\n";
            Quiz.RightAnswers++;
        }
        else
        {
            SetRed();
            cout << "Wrong! Correct Answer: "
                 << Quiz.Questions[i].CorrectAnswer << "\n";
            Quiz.WrongAnswers++;
        }
        ResetColor();
    }
}

/* =======================
   PLAY GAME
======================= */
void PlayMathGame()
{
    stQuiz Quiz;

    cout << "How many questions [1-100]? ";
    cin >> Quiz.NumberOfQuestions;

    int Choice;

    cout << "\nChoose Questions Level:\n";
    cout << "1) Easy\n2) Medium\n3) Hard\n4) Mix\n";
    cin >> Choice;
    Quiz.Level = (enQuestionsLevel)Choice;

    cout << "\nChoose Operation Type:\n";
    cout << "1) +\n2) -\n3) x\n4) /\n5) Mix\n";
    cin >> Choice;
    Quiz.OpType = (enOperationType)Choice;

    for (short i = 0; i < Quiz.NumberOfQuestions; i++)
    {
        Quiz.Questions[i] = GenerateQuestion(Quiz.Level, Quiz.OpType);
    }

    AskQuestions(Quiz);

    cout << "\n------------------------------\n";
    cout << "Questions : " << Quiz.NumberOfQuestions << "\n";
    cout << "Right     : " << Quiz.RightAnswers << "\n";
    cout << "Wrong     : " << Quiz.WrongAnswers << "\n";
    cout << "Level     : " << GetQuestionLevelText(Quiz.Level) << "\n";

    if (Quiz.RightAnswers >= Quiz.WrongAnswers)
    {
        SetGreen();
        cout << "Result    : PASS ✅\n";
    }
    else
    {
        SetRed();
        cout << "Result    : FAIL ❌\n";
    }
    ResetColor();
    cout << "------------------------------\n";
}

/* =======================
   MAIN
======================= */
int main()
{
    srand((unsigned)time(NULL));

    char PlayAgain;
    do
    {
        system("clear");
        PlayMathGame();
        cout << "\nPlay Again? Y/N ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

    return 0;
}