#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>
using namespace std;

// Helper function to convert int to string (for Dev-C++ compatibility)
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

// Color codes for Windows console
enum Colors {
    DEFAULT = 7,
    BLUE = 9,
    GREEN = 10,
    RED = 12,
    YELLOW = 14,
    MAGENTA = 13,
    CYAN = 11,
    WHITE = 15,
    LIGHT_GREEN = 2,
    LIGHT_RED = 4,
    LIGHT_BLUE = 3
};

// Structure to store a question
struct Question {
    string questionText;
    string options[4];
    char correctAnswer;
    int points;
    string category;
    string type; // Added: "MCQ" or "TF"
};

// Structure to store player score
struct PlayerScore {
    string name;
    int score;
    string difficulty;
    string category;
    string quizType; // Added: "MCQ" or "True/False"
    time_t date;
};

// Global variables
vector<PlayerScore> highScores;

// Function to set text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to reset color to default
void resetColor() {
    setColor(DEFAULT);
}

// Function to clear screen
void clearScreen() {
    system("cls");
}

// Function to display header
void printHeader(string title) {
    setColor(CYAN);
    cout << "           " << title << endl;
    resetColor();
}

// Function to display animated message
void displayAnimation(string message, int color) {
    setColor(color);
    for (unsigned int i = 0; i < message.length(); i++) {
        cout << message[i] << flush;
        Sleep(50);
    }
    cout << endl;
    resetColor();
}

// Function to validate answer input for MCQ
bool isValidMCQAnswer(char answer) {
    answer = toupper(answer);
    return answer >= 'A' && answer <= 'D';
}

// Function to validate answer input for True/False
bool isValidTFAnswer(char answer) {
    answer = toupper(answer);
    return answer == 'T' || answer == 'F';
}

// Function to ask an MCQ question
int askMCQQuestion(Question q, int questionNum, int totalQuestions) {
    clearScreen();
    
    setColor(LIGHT_BLUE);
    cout << "Category: " << q.category << endl;
    
    setColor(MAGENTA);
    cout << "\nQuestion " << questionNum << " of " << totalQuestions;
    cout << " (Points: " << q.points << ")" << endl;
    cout << "Type: Multiple Choice (MCQ)" << endl;
    
    setColor(YELLOW);
    cout << "\n" << q.questionText << endl;
    
    setColor(GREEN);
    for (int i = 0; i < 4; i++) {
        cout << q.options[i] << endl;
    }
    
    setColor(BLUE);
    cout << "\nYou have 15 seconds to answer!" << endl;
    cout << "Enter your answer (A/B/C/D): ";
    cout.flush();
    
    // Start timer
    time_t startTime = time(NULL);
    char answer = ' ';
    bool timeUp = false;
    
    // Get user input with timeout
    while (difftime(time(NULL), startTime) < 15) {
        if (_kbhit()) {
            answer = _getch();
            
            if (answer >= 'a' && answer <= 'd') {
                answer = answer - 32;
            }
            
            if (isValidMCQAnswer(answer)) {
                cout << answer << endl;
                break;
            }
        }
        Sleep(100);
    }
    
    // Check if time's up
    if (difftime(time(NULL), startTime) >= 15 && answer == ' ') {
        timeUp = true;
        cout << "\nTime's up!" << endl;
    }
    
    // Check answer
    if (answer == q.correctAnswer) {
        displayAnimation("Correct! +" + intToString(q.points) + " points", LIGHT_GREEN);
        return q.points;
    } else if (timeUp) {
        displayAnimation("Time's up!", RED);
    } else {
        displayAnimation("Wrong!", LIGHT_RED);
    }
    
    setColor(YELLOW);
    cout << "Correct answer is: " << q.correctAnswer << endl;
    resetColor();
    
    Sleep(2000);
    return 0;
}

// Function to ask a True/False question
int askTFQuestion(Question q, int questionNum, int totalQuestions) {
    clearScreen();
    
    setColor(LIGHT_BLUE);
    cout << "Category: " << q.category << endl;
    
    setColor(MAGENTA);
    cout << "\nQuestion " << questionNum << " of " << totalQuestions;
    cout << " (Points: " << q.points << ")" << endl;
    cout << "Type: True/False" << endl;
    
    setColor(YELLOW);
    cout << "\n" << q.questionText << endl;
    
    // Show True/False options
    setColor(GREEN);
    cout << "\nT. True" << endl;
    cout << "F. False" << endl;
    
    setColor(BLUE);
    cout << "\nYou have 10 seconds to answer!" << endl;
    cout << "Enter your answer (T/F): ";
    cout.flush();
    
    // Start timer
    time_t startTime = time(NULL);
    char answer = ' ';
    bool timeUp = false;
    
    // Get user input with timeout
    while (difftime(time(NULL), startTime) < 10) {
        if (_kbhit()) {
            answer = _getch();
            
            if (answer == 't' || answer == 'T') {
                answer = 'T';
                cout << "T" << endl;
                break;
            } else if (answer == 'f' || answer == 'F') {
                answer = 'F';
                cout << "F" << endl;
                break;
            }
        }
        Sleep(100);
    }
    
    // Check if time's up
    if (difftime(time(NULL), startTime) >= 10 && answer == ' ') {
        timeUp = true;
        cout << "\nTime's up!" << endl;
    }
    
    // Check answer
    if (answer == q.correctAnswer) {
        displayAnimation("Correct! +" + intToString(q.points) + " points", LIGHT_GREEN);
        return q.points;
    } else if (timeUp) {
        displayAnimation("Time's up!", RED);
    } else {
        displayAnimation("Wrong!", LIGHT_RED);
    }
    
    setColor(YELLOW);
    cout << "Correct answer is: " << (q.correctAnswer == 'T' ? "True" : "False") << endl;
    resetColor();
    
    Sleep(2000);
    return 0;
}

// Function to ask a question (handles both types)
int askQuestion(Question q, int questionNum, int totalQuestions) {
    if (q.type == "TF") {
        return askTFQuestion(q, questionNum, totalQuestions);
    } else {
        return askMCQQuestion(q, questionNum, totalQuestions);
    }
}

// Function to shuffle questions
void shuffleQuestions(vector<Question>& questions) {
    srand(time(NULL));
    for (unsigned int i = 0; i < questions.size(); i++) {
        int randomIndex = rand() % questions.size();
        swap(questions[i], questions[randomIndex]);
    }
}

// Function to start quiz
int startQuiz(vector<Question>& questions, string difficulty, string category, string playerName, string quizType) {
    int score = 0;
    int totalQuestions = questions.size();
    
    clearScreen();
    printHeader("QUIZ STARTED - " + difficulty + " (" + category + ")");
    
    setColor(WHITE);
    cout << "\nPlayer: " << playerName << endl;
    cout << "Quiz Type: " << quizType << endl;
    cout << "Difficulty: " << difficulty << endl;
    cout << "Category: " << category << endl;
    cout << "Total Questions: " << totalQuestions << endl;
    cout << "\nPress Enter to begin...";
    cin.ignore();
    cin.get();
    
    shuffleQuestions(questions);
    
    for (unsigned int i = 0; i < questions.size(); i++) {
        score += askQuestion(questions[i], i + 1, totalQuestions);
        
        setColor(BLUE);
        cout << "\nCurrent Score: " << score << " points" << endl;
        cout << "----------------------------------------" << endl;
        Sleep(1000);
    }
    
    return score;
}

// Function to save high score
void saveHighScore(const PlayerScore& score) {
    highScores.push_back(score);
    
    // Sort in descending order by score
    for (unsigned int i = 0; i < highScores.size(); i++) {
        for (unsigned int j = i + 1; j < highScores.size(); j++) {
            if (highScores[i].score < highScores[j].score) {
                swap(highScores[i], highScores[j]);
            }
        }
    }
    
    if (highScores.size() > 10) {
        highScores.resize(10);
    }
    
    ofstream file("highscores.txt");
    if (file.is_open()) {
        for (unsigned int i = 0; i < highScores.size(); i++) {
            file << highScores[i].name << "," 
                 << highScores[i].score << "," 
                 << highScores[i].difficulty << ","
                 << highScores[i].category << ","
                 << highScores[i].quizType << ","
                 << highScores[i].date << endl;
        }
        file.close();
    }
}

// Function to load high scores
void loadHighScores() {
    ifstream file("highscores.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, difficulty, category, quizType;
            int score;
            time_t date;
            
            getline(ss, name, ',');
            
            string scoreStr;
            getline(ss, scoreStr, ',');
            score = atoi(scoreStr.c_str());
            
            getline(ss, difficulty, ',');
            getline(ss, category, ',');
            getline(ss, quizType, ',');
            
            string dateStr;
            getline(ss, dateStr);
            date = (time_t)atol(dateStr.c_str());
            
            PlayerScore newScore;
            newScore.name = name;
            newScore.score = score;
            newScore.difficulty = difficulty;
            newScore.category = category;
            newScore.quizType = quizType;
            newScore.date = date;
            
            highScores.push_back(newScore);
        }
        file.close();
    }
}

// Function to display high scores
void showHighScores() {
    clearScreen();
    printHeader("HIGH SCORES");
    
    if (highScores.empty()) {
        setColor(YELLOW);
        cout << "\nNo high scores yet! Be the first!" << endl;
    } else {
        setColor(CYAN);
        cout << "\nRank  Name              Score  Type       Difficulty  Category       Date" << endl;
        cout << "================================================================================" << endl;
        
        for (unsigned int i = 0; i < highScores.size() && i < 10; i++) {
            const PlayerScore& hs = highScores[i];
            tm* timeinfo = localtime(&hs.date);
            char buffer[80];
            strftime(buffer, 80, "%Y-%m-%d", timeinfo);
            
            if (i == 0) {
                setColor(YELLOW);
            } else if (i < 3) {
                setColor(MAGENTA);
            } else {
                setColor(WHITE);
            }
            
            printf("%2d.   %-15s %5d  %-10s %-10s  %-12s  %s\n", 
                   i + 1, hs.name.c_str(), hs.score, 
                   hs.quizType.c_str(), hs.difficulty.c_str(), hs.category.c_str(), buffer);
        }
    }
    
    resetColor();
    cout << "\n\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Function to display instructions
void showInstructions() {
    clearScreen();
    printHeader("INSTRUCTIONS");
    
    setColor(WHITE);
    cout << "\nHOW TO PLAY:\n" << endl;
    setColor(GREEN);
    cout << "1. Choose a quiz type (MCQ or True/False)" << endl;
    cout << "2. Choose a quiz category (General Knowledge/Math/Science)" << endl;
    cout << "3. Choose a difficulty level (Easy/Medium/Hard)" << endl;
    
    setColor(CYAN);
    cout << "\nFOR MCQ QUIZ:" << endl;
    cout << "• Answer multiple-choice questions (A/B/C/D)" << endl;
    cout << "• You have 15 seconds per question" << endl;
    
    setColor(MAGENTA);
    cout << "\nFOR TRUE/FALSE QUIZ:" << endl;
    cout << "• Answer True (T) or False (F) questions" << endl;
    cout << "• You have 10 seconds per question" << endl;
    
    setColor(GREEN);
    cout << "\nPOINTS SYSTEM:" << endl;
    cout << "• Easy: 10 points per question" << endl;
    cout << "• Medium: 20 points per question" << endl;
    cout << "• Hard: 30 points per question" << endl;
    cout << "6. Your score will be saved in high scores" << endl;
    
    setColor(YELLOW);
    cout << "\nSCORING:" << endl;
    cout << "• Excellent: 80% or above" << endl;
    cout << "• Good: 60% - 79%" << endl;
    cout << "• Fair: 40% - 59%" << endl;
    cout << "• Needs Improvement: Below 40%" << endl;
    
    resetColor();
    cout << "\n\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Function to select quiz type
int selectQuizType() {
    clearScreen();
    printHeader("SELECT QUIZ TYPE");
    
    setColor(WHITE);
    cout << "\n1. Multiple Choice Quiz (MCQ)" << endl;
    cout << "2. True/False Quiz" << endl;
    cout << "3. Back to Main Menu" << endl;
    
    setColor(YELLOW);
    cout << "\nEnter your choice (1-3): ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return 0;
    }
    cin.ignore();
    
    return choice;
}

// Function to select quiz category
int selectCategory() {
    clearScreen();
    printHeader("SELECT QUIZ CATEGORY");
    
    setColor(WHITE);
    cout << "\n1. General Knowledge" << endl;
    cout << "2. Mathematics" << endl;
    cout << "3. Science" << endl;
    cout << "4. Back to Quiz Type Selection" << endl;
    
    setColor(YELLOW);
    cout << "\nEnter your choice (1-4): ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return 0;
    }
    cin.ignore();
    
    return choice;
}

// Function to select difficulty level
int selectDifficulty() {
    clearScreen();
    printHeader("SELECT DIFFICULTY");
    
    setColor(WHITE);
    cout << "\n1. Easy (10 points per question)" << endl;
    cout << "2. Medium (20 points per question)" << endl;
    cout << "3. Hard (30 points per question)" << endl;
    cout << "4. Back to Category Selection" << endl;
    
    setColor(YELLOW);
    cout << "\nEnter your choice (1-4): ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return 0;
    }
    cin.ignore();
    
    return choice;
}

int main() {
    srand(time(NULL));
    loadHighScores();
    
    // Initialize questions for different categories, difficulties, and types
    vector<Question> easyGK_MCQ, mediumGK_MCQ, hardGK_MCQ;
    vector<Question> easyMath_MCQ, mediumMath_MCQ, hardMath_MCQ;
    vector<Question> easyScience_MCQ, mediumScience_MCQ, hardScience_MCQ;
    
    // True/False questions
    vector<Question> easyGK_TF, mediumGK_TF, hardGK_TF;
    vector<Question> easyMath_TF, mediumMath_TF, hardMath_TF;
    vector<Question> easyScience_TF, mediumScience_TF, hardScience_TF;
    
    // ========== EASY GENERAL KNOWLEDGE MCQ QUESTIONS ==========
    Question gk1; gk1.questionText = "What is the capital of France?"; 
    gk1.options[0] = "A. Paris"; gk1.options[1] = "B. London"; 
    gk1.options[2] = "C. Rome"; gk1.options[3] = "D. Madrid";
    gk1.correctAnswer = 'A'; gk1.points = 10; gk1.category = "General Knowledge";
    gk1.type = "MCQ";
    easyGK_MCQ.push_back(gk1);
    
    Question gk2; gk2.questionText = "Which planet is known as the Red Planet?"; 
    gk2.options[0] = "A. Earth"; gk2.options[1] = "B. Mars"; 
    gk2.options[2] = "C. Jupiter"; gk2.options[3] = "D. Venus";
    gk2.correctAnswer = 'B'; gk2.points = 10; gk2.category = "General Knowledge";
    gk2.type = "MCQ";
    easyGK_MCQ.push_back(gk2);
    
    Question gk3; gk3.questionText = "What is the largest ocean on Earth?"; 
    gk3.options[0] = "A. Atlantic Ocean"; gk3.options[1] = "B. Indian Ocean"; 
    gk3.options[2] = "C. Pacific Ocean"; gk3.options[3] = "D. Arctic Ocean";
    gk3.correctAnswer = 'C'; gk3.points = 10; gk3.category = "General Knowledge";
    gk3.type = "MCQ";
    easyGK_MCQ.push_back(gk3);
    
    Question gk4; gk4.questionText = "Which country is known as the Land of the Rising Sun?"; 
    gk4.options[0] = "A. China"; gk4.options[1] = "B. Japan"; 
    gk4.options[2] = "C. Thailand"; gk4.options[3] = "D. South Korea";
    gk4.correctAnswer = 'B'; gk4.points = 10; gk4.category = "General Knowledge";
    gk4.type = "MCQ";
    easyGK_MCQ.push_back(gk4);
    
    Question gk5; gk5.questionText = "What is the currency of the United States?"; 
    gk5.options[0] = "A. Euro"; gk5.options[1] = "B. Pound"; 
    gk5.options[2] = "C. Dollar"; gk5.options[3] = "D. Yen";
    gk5.correctAnswer = 'C'; gk5.points = 10; gk5.category = "General Knowledge";
    gk5.type = "MCQ";
    easyGK_MCQ.push_back(gk5);
    
    // ========== EASY GENERAL KNOWLEDGE TRUE/FALSE QUESTIONS ==========
    Question gk1_tf; gk1_tf.questionText = "Paris is the capital of France."; 
    gk1_tf.options[0] = "T. True"; gk1_tf.options[1] = "F. False"; 
    gk1_tf.options[2] = ""; gk1_tf.options[3] = "";
    gk1_tf.correctAnswer = 'T'; gk1_tf.points = 10; gk1_tf.category = "General Knowledge";
    gk1_tf.type = "TF";
    easyGK_TF.push_back(gk1_tf);
    
    Question gk2_tf; gk2_tf.questionText = "The Pacific Ocean is the largest ocean on Earth."; 
    gk2_tf.options[0] = "T. True"; gk2_tf.options[1] = "F. False"; 
    gk2_tf.options[2] = ""; gk2_tf.options[3] = "";
    gk2_tf.correctAnswer = 'T'; gk2_tf.points = 10; gk2_tf.category = "General Knowledge";
    gk2_tf.type = "TF";
    easyGK_TF.push_back(gk2_tf);
    
    Question gk3_tf; gk3_tf.questionText = "The currency of Japan is the Yuan."; 
    gk3_tf.options[0] = "T. True"; gk3_tf.options[1] = "F. False"; 
    gk3_tf.options[2] = ""; gk3_tf.options[3] = "";
    gk3_tf.correctAnswer = 'F'; gk3_tf.points = 10; gk3_tf.category = "General Knowledge";
    gk3_tf.type = "TF";
    easyGK_TF.push_back(gk3_tf);
    
    Question gk4_tf; gk4_tf.questionText = "Mount Everest is the tallest mountain in the world."; 
    gk4_tf.options[0] = "T. True"; gk4_tf.options[1] = "F. False"; 
    gk4_tf.options[2] = ""; gk4_tf.options[3] = "";
    gk4_tf.correctAnswer = 'T'; gk4_tf.points = 10; gk4_tf.category = "General Knowledge";
    gk4_tf.type = "TF";
    easyGK_TF.push_back(gk4_tf);
    
    Question gk5_tf; gk5_tf.questionText = "There are 7 continents on Earth."; 
    gk5_tf.options[0] = "T. True"; gk5_tf.options[1] = "F. False"; 
    gk5_tf.options[2] = ""; gk5_tf.options[3] = "";
    gk5_tf.correctAnswer = 'T'; gk5_tf.points = 10; gk5_tf.category = "General Knowledge";
    gk5_tf.type = "TF";
    easyGK_TF.push_back(gk5_tf);
    
    // ========== MEDIUM GENERAL KNOWLEDGE MCQ QUESTIONS ==========
    Question gk6; gk6.questionText = "Who wrote the play 'Romeo and Juliet'?"; 
    gk6.options[0] = "A. Charles Dickens"; gk6.options[1] = "B. William Shakespeare"; 
    gk6.options[2] = "C. Jane Austen"; gk6.options[3] = "D. Mark Twain";
    gk6.correctAnswer = 'B'; gk6.points = 20; gk6.category = "General Knowledge";
    gk6.type = "MCQ";
    mediumGK_MCQ.push_back(gk6);
    
    Question gk7; gk7.questionText = "What is the tallest mountain in the world?"; 
    gk7.options[0] = "A. K2"; gk7.options[1] = "B. Mount Everest"; 
    gk7.options[2] = "C. Kangchenjunga"; gk7.options[3] = "D. Makalu";
    gk7.correctAnswer = 'B'; gk7.points = 20; gk7.category = "General Knowledge";
    gk7.type = "MCQ";
    mediumGK_MCQ.push_back(gk7);
    
    Question gk8; gk8.questionText = "Which element has the chemical symbol 'Au'?"; 
    gk8.options[0] = "A. Silver"; gk8.options[1] = "B. Gold"; 
    gk8.options[2] = "C. Aluminum"; gk8.options[3] = "D. Iron";
    gk8.correctAnswer = 'B'; gk8.points = 20; gk8.category = "General Knowledge";
    gk8.type = "MCQ";
    mediumGK_MCQ.push_back(gk8);
    
    // ========== MEDIUM GENERAL KNOWLEDGE TRUE/FALSE QUESTIONS ==========
    Question gk6_tf; gk6_tf.questionText = "William Shakespeare wrote 'Hamlet'."; 
    gk6_tf.options[0] = "T. True"; gk6_tf.options[1] = "F. False"; 
    gk6_tf.options[2] = ""; gk6_tf.options[3] = "";
    gk6_tf.correctAnswer = 'T'; gk6_tf.points = 20; gk6_tf.category = "General Knowledge";
    gk6_tf.type = "TF";
    mediumGK_TF.push_back(gk6_tf);
    
    Question gk7_tf; gk7_tf.questionText = "The chemical symbol for gold is 'Go'."; 
    gk7_tf.options[0] = "T. True"; gk7_tf.options[1] = "F. False"; 
    gk7_tf.options[2] = ""; gk7_tf.options[3] = "";
    gk7_tf.correctAnswer = 'F'; gk7_tf.points = 20; gk7_tf.category = "General Knowledge";
    gk7_tf.type = "TF";
    mediumGK_TF.push_back(gk7_tf);
    
    Question gk8_tf; gk8_tf.questionText = "The Nile is the longest river in the world."; 
    gk8_tf.options[0] = "T. True"; gk8_tf.options[1] = "F. False"; 
    gk8_tf.options[2] = ""; gk8_tf.options[3] = "";
    gk8_tf.correctAnswer = 'T'; gk8_tf.points = 20; gk8_tf.category = "General Knowledge";
    gk8_tf.type = "TF";
    mediumGK_TF.push_back(gk8_tf);
    
    // ========== HARD GENERAL KNOWLEDGE MCQ QUESTIONS ==========
    Question gk11; gk11.questionText = "Who painted the 'Mona Lisa'?"; 
    gk11.options[0] = "A. Vincent van Gogh"; gk11.options[1] = "B. Leonardo da Vinci"; 
    gk11.options[2] = "C. Pablo Picasso"; gk11.options[3] = "D. Michelangelo";
    gk11.correctAnswer = 'B'; gk11.points = 30; gk11.category = "General Knowledge";
    gk11.type = "MCQ";
    hardGK_MCQ.push_back(gk11);
    
    Question gk12; gk12.questionText = "What is the longest river in the world?"; 
    gk12.options[0] = "A. Amazon River"; gk12.options[1] = "B. Nile River"; 
    gk12.options[2] = "C. Yangtze River"; gk12.options[3] = "D. Mississippi River";
    gk12.correctAnswer = 'B'; gk12.points = 30; gk12.category = "General Knowledge";
    gk12.type = "MCQ";
    hardGK_MCQ.push_back(gk12);
    
    Question gk13; gk13.questionText = "Which language has the most native speakers?"; 
    gk13.options[0] = "A. English"; gk13.options[1] = "B. Spanish"; 
    gk13.options[2] = "C. Hindi"; gk13.options[3] = "D. Mandarin Chinese";
    gk13.correctAnswer = 'D'; gk13.points = 30; gk13.category = "General Knowledge";
    gk13.type = "MCQ";
    hardGK_MCQ.push_back(gk13);
    
    // ========== HARD GENERAL KNOWLEDGE TRUE/FALSE QUESTIONS ==========
    Question gk11_tf; gk11_tf.questionText = "Leonardo da Vinci painted the 'Starry Night'."; 
    gk11_tf.options[0] = "T. True"; gk11_tf.options[1] = "F. False"; 
    gk11_tf.options[2] = ""; gk11_tf.options[3] = "";
    gk11_tf.correctAnswer = 'F'; gk11_tf.points = 30; gk11_tf.category = "General Knowledge";
    gk11_tf.type = "TF";
    hardGK_TF.push_back(gk11_tf);
    
    Question gk12_tf; gk12_tf.questionText = "Mandarin Chinese has the most native speakers worldwide."; 
    gk12_tf.options[0] = "T. True"; gk12_tf.options[1] = "F. False"; 
    gk12_tf.options[2] = ""; gk12_tf.options[3] = "";
    gk12_tf.correctAnswer = 'T'; gk12_tf.points = 30; gk12_tf.category = "General Knowledge";
    gk12_tf.type = "TF";
    hardGK_TF.push_back(gk12_tf);
    
    Question gk13_tf; gk13_tf.questionText = "The Amazon River is longer than the Nile River."; 
    gk13_tf.options[0] = "T. True"; gk13_tf.options[1] = "F. False"; 
    gk13_tf.options[2] = ""; gk13_tf.options[3] = "";
    gk13_tf.correctAnswer = 'F'; gk13_tf.points = 30; gk13_tf.category = "General Knowledge";
    gk13_tf.type = "TF";
    hardGK_TF.push_back(gk13_tf);
    
    // ========== EASY MATHEMATICS MCQ QUESTIONS ==========
    Question m1; m1.questionText = "What is 15 + 27?"; 
    m1.options[0] = "A. 40"; m1.options[1] = "B. 42"; 
    m1.options[2] = "C. 44"; m1.options[3] = "D. 45";
    m1.correctAnswer = 'B'; m1.points = 10; m1.category = "Mathematics";
    m1.type = "MCQ";
    easyMath_MCQ.push_back(m1);
    
    Question m2; m2.questionText = "What is 9 × 8?"; 
    m2.options[0] = "A. 64"; m2.options[1] = "B. 72"; 
    m2.options[2] = "C. 81"; m2.options[3] = "D. 90";
    m2.correctAnswer = 'B'; m2.points = 10; m2.category = "Mathematics";
    m2.type = "MCQ";
    easyMath_MCQ.push_back(m2);
    
    Question m3; m3.questionText = "What is 144 ÷ 12?"; 
    m3.options[0] = "A. 10"; m3.options[1] = "B. 11"; 
    m3.options[2] = "C. 12"; m3.options[3] = "D. 13";
    m3.correctAnswer = 'C'; m3.points = 10; m3.category = "Mathematics";
    m3.type = "MCQ";
    easyMath_MCQ.push_back(m3);
    
    // ========== EASY MATHEMATICS TRUE/FALSE QUESTIONS ==========
    Question m1_tf; m1_tf.questionText = "15 + 27 equals 42."; 
    m1_tf.options[0] = "T. True"; m1_tf.options[1] = "F. False"; 
    m1_tf.options[2] = ""; m1_tf.options[3] = "";
    m1_tf.correctAnswer = 'T'; m1_tf.points = 10; m1_tf.category = "Mathematics";
    m1_tf.type = "TF";
    easyMath_TF.push_back(m1_tf);
    
    Question m2_tf; m2_tf.questionText = "9 multiplied by 8 equals 72."; 
    m2_tf.options[0] = "T. True"; m2_tf.options[1] = "F. False"; 
    m2_tf.options[2] = ""; m2_tf.options[3] = "";
    m2_tf.correctAnswer = 'T'; m2_tf.points = 10; m2_tf.category = "Mathematics";
    m2_tf.type = "TF";
    easyMath_TF.push_back(m2_tf);
    
    Question m3_tf; m3_tf.questionText = "144 divided by 12 equals 11."; 
    m3_tf.options[0] = "T. True"; m3_tf.options[1] = "F. False"; 
    m3_tf.options[2] = ""; m3_tf.options[3] = "";
    m3_tf.correctAnswer = 'F'; m3_tf.points = 10; m3_tf.category = "Mathematics";
    m3_tf.type = "TF";
    easyMath_TF.push_back(m3_tf);
    
    // ========== EASY SCIENCE MCQ QUESTIONS ==========
    Question s1; s1.questionText = "What gas do plants absorb from the atmosphere?"; 
    s1.options[0] = "A. Oxygen"; s1.options[1] = "B. Carbon Dioxide"; 
    s1.options[2] = "C. Nitrogen"; s1.options[3] = "D. Hydrogen";
    s1.correctAnswer = 'B'; s1.points = 10; s1.category = "Science";
    s1.type = "MCQ";
    easyScience_MCQ.push_back(s1);
    
    Question s2; s2.questionText = "What is the closest planet to the Sun?"; 
    s2.options[0] = "A. Venus"; s2.options[1] = "B. Earth"; 
    s2.options[2] = "C. Mercury"; s2.options[3] = "D. Mars";
    s2.correctAnswer = 'C'; s2.points = 10; s2.category = "Science";
    s2.type = "MCQ";
    easyScience_MCQ.push_back(s2);
    
    Question s3; s3.questionText = "What is H2O commonly known as?"; 
    s3.options[0] = "A. Salt"; s3.options[1] = "B. Sugar"; 
    s3.options[2] = "C. Water"; s3.options[3] = "D. Acid";
    s3.correctAnswer = 'C'; s3.points = 10; s3.category = "Science";
    s3.type = "MCQ";
    easyScience_MCQ.push_back(s3);
    
    // ========== EASY SCIENCE TRUE/FALSE QUESTIONS ==========
    Question s1_tf; s1_tf.questionText = "Plants absorb carbon dioxide from the atmosphere."; 
    s1_tf.options[0] = "T. True"; s1_tf.options[1] = "F. False"; 
    s1_tf.options[2] = ""; s1_tf.options[3] = "";
    s1_tf.correctAnswer = 'T'; s1_tf.points = 10; s1_tf.category = "Science";
    s1_tf.type = "TF";
    easyScience_TF.push_back(s1_tf);
    
    Question s2_tf; s2_tf.questionText = "Mercury is the closest planet to the Sun."; 
    s2_tf.options[0] = "T. True"; s2_tf.options[1] = "F. False"; 
    s2_tf.options[2] = ""; s2_tf.options[3] = "";
    s2_tf.correctAnswer = 'T'; s2_tf.points = 10; s2_tf.category = "Science";
    s2_tf.type = "TF";
    easyScience_TF.push_back(s2_tf);
    
    Question s3_tf; s3_tf.questionText = "H2O is the chemical formula for salt."; 
    s3_tf.options[0] = "T. True"; s3_tf.options[1] = "F. False"; 
    s3_tf.options[2] = ""; s3_tf.options[3] = "";
    s3_tf.correctAnswer = 'F'; s3_tf.points = 10; s3_tf.category = "Science";
    s3_tf.type = "TF";
    easyScience_TF.push_back(s3_tf);
    
    // For Medium and Hard levels, create similar questions with different points
    mediumMath_MCQ = easyMath_MCQ;
    hardMath_MCQ = easyMath_MCQ;
    mediumScience_MCQ = easyScience_MCQ;
    hardScience_MCQ = easyScience_MCQ;
    
    mediumMath_TF = easyMath_TF;
    hardMath_TF = easyMath_TF;
    mediumScience_TF = easyScience_TF;
    hardScience_TF = easyScience_TF;
    
    // Update points for medium and hard levels
    for (unsigned int i = 0; i < mediumMath_MCQ.size(); i++) {
        mediumMath_MCQ[i].points = 20;
    }
    for (unsigned int i = 0; i < hardMath_MCQ.size(); i++) {
        hardMath_MCQ[i].points = 30;
    }
    for (unsigned int i = 0; i < mediumScience_MCQ.size(); i++) {
        mediumScience_MCQ[i].points = 20;
    }
    for (unsigned int i = 0; i < hardScience_MCQ.size(); i++) {
        hardScience_MCQ[i].points = 30;
    }
    
    for (unsigned int i = 0; i < mediumMath_TF.size(); i++) {
        mediumMath_TF[i].points = 20;
    }
    for (unsigned int i = 0; i < hardMath_TF.size(); i++) {
        hardMath_TF[i].points = 30;
    }
    for (unsigned int i = 0; i < mediumScience_TF.size(); i++) {
        mediumScience_TF[i].points = 20;
    }
    for (unsigned int i = 0; i < hardScience_TF.size(); i++) {
        hardScience_TF[i].points = 30;
    }
    
    string playerName;
    
    clearScreen();
    printHeader("WELCOME TO QUIZ GAME");
    
    setColor(YELLOW);
    cout << "\nEnter your name: ";
    getline(cin, playerName);
    
    if (playerName.empty()) {
        playerName = "Quiz Master";
    }
    
    int choice;
    do {
        clearScreen();
        printHeader("MAIN MENU");
        
        setColor(CYAN);
        cout << "\nPlayer: " << playerName << endl;
        cout << "==========================================" << endl;
        
        setColor(WHITE);
        cout << "1. Start New Quiz" << endl;
        cout << "2. View Instructions" << endl;
        cout << "3. View High Scores" << endl;
        cout << "4. Change Player Name" << endl;
        cout << "5. Exit Game" << endl;
        
        setColor(YELLOW);
        cout << "\nEnter your choice (1-5): ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }
        cin.ignore();
        
        switch (choice) {
            case 1: { // Start Quiz
                int quizTypeChoice = selectQuizType();
                
                if (quizTypeChoice == 3) continue;
                if (quizTypeChoice < 1 || quizTypeChoice > 2) {
                    setColor(RED);
                    cout << "Invalid quiz type choice!" << endl;
                    Sleep(1000);
                    continue;
                }
                
                int categoryChoice = selectCategory();
                
                if (categoryChoice == 4) continue;
                if (categoryChoice < 1 || categoryChoice > 3) {
                    setColor(RED);
                    cout << "Invalid category choice!" << endl;
                    Sleep(1000);
                    continue;
                }
                
                int difficultyChoice = selectDifficulty();
                
                if (difficultyChoice == 4) continue;
                if (difficultyChoice < 1 || difficultyChoice > 3) {
                    setColor(RED);
                    cout << "Invalid difficulty choice!" << endl;
                    Sleep(1000);
                    continue;
                }
                
                string category, difficulty, quizType;
                vector<Question> selectedQuestions;
                
                // Set quiz type
                switch (quizTypeChoice) {
                    case 1: quizType = "MCQ"; break;
                    case 2: quizType = "True/False"; break;
                }
                
                // Set category
                switch (categoryChoice) {
                    case 1: category = "General Knowledge"; break;
                    case 2: category = "Mathematics"; break;
                    case 3: category = "Science"; break;
                }
                
                // Set difficulty and questions based on quiz type
                if (quizTypeChoice == 1) { // MCQ
                    switch (difficultyChoice) {
                        case 1:
                            difficulty = "Easy";
                            if (categoryChoice == 1) selectedQuestions = easyGK_MCQ;
                            else if (categoryChoice == 2) selectedQuestions = easyMath_MCQ;
                            else selectedQuestions = easyScience_MCQ;
                            break;
                        case 2:
                            difficulty = "Medium";
                            if (categoryChoice == 1) selectedQuestions = mediumGK_MCQ;
                            else if (categoryChoice == 2) selectedQuestions = mediumMath_MCQ;
                            else selectedQuestions = mediumScience_MCQ;
                            break;
                        case 3:
                            difficulty = "Hard";
                            if (categoryChoice == 1) selectedQuestions = hardGK_MCQ;
                            else if (categoryChoice == 2) selectedQuestions = hardMath_MCQ;
                            else selectedQuestions = hardScience_MCQ;
                            break;
                    }
                } else { // True/False
                    switch (difficultyChoice) {
                        case 1:
                            difficulty = "Easy";
                            if (categoryChoice == 1) selectedQuestions = easyGK_TF;
                            else if (categoryChoice == 2) selectedQuestions = easyMath_TF;
                            else selectedQuestions = easyScience_TF;
                            break;
                        case 2:
                            difficulty = "Medium";
                            if (categoryChoice == 1) selectedQuestions = mediumGK_TF;
                            else if (categoryChoice == 2) selectedQuestions = mediumMath_TF;
                            else selectedQuestions = mediumScience_TF;
                            break;
                        case 3:
                            difficulty = "Hard";
                            if (categoryChoice == 1) selectedQuestions = hardGK_TF;
                            else if (categoryChoice == 2) selectedQuestions = hardMath_TF;
                            else selectedQuestions = hardScience_TF;
                            break;
                    }
                }
                
                int score = startQuiz(selectedQuestions, difficulty, category, playerName, quizType);
                
                // Display results
                clearScreen();
                printHeader("QUIZ COMPLETE!");
                
                if (selectedQuestions.size() > 0) {
                    int totalPossible = selectedQuestions.size() * selectedQuestions[0].points;
                    int percentage = (score * 100) / totalPossible;
                    
                    if (percentage >= 80) setColor(LIGHT_GREEN);
                    else if (percentage >= 60) setColor(GREEN);
                    else if (percentage >= 40) setColor(YELLOW);
                    else setColor(RED);
                    
                    cout << "\nFINAL RESULTS\n" << endl;
                    
                    setColor(WHITE);
                    cout << "Player: " << playerName << endl;
                    cout << "Quiz Type: " << quizType << endl;
                    cout << "Category: " << category << endl;
                    cout << "Difficulty: " << difficulty << endl;
                    cout << "Total Questions: " << selectedQuestions.size() << endl;
                    
                    setColor(CYAN);
                    cout << "\n========================================" << endl;
                    cout << "YOUR SCORE: " << score << "/" << totalPossible << " points" << endl;
                    cout << "Percentage: " << percentage << "%" << endl;
                    
                    // Display grade message
                    setColor(WHITE);
                    cout << "\nGrade: ";
                    if (percentage >= 80) {
                        displayAnimation("EXCELLENT!", YELLOW);
                    } else if (percentage >= 60) {
                        displayAnimation("GOOD JOB!", GREEN);
                    } else if (percentage >= 40) {
                        displayAnimation("FAIR - Keep Practicing!", MAGENTA);
                    } else {
                        displayAnimation("Needs Improvement - Try Again!", RED);
                    }
                    
                    // Save high score
                    PlayerScore newScore;
                    newScore.name = playerName;
                    newScore.score = score;
                    newScore.difficulty = difficulty;
                    newScore.category = category;
                    newScore.quizType = quizType;
                    newScore.date = time(NULL);
                    saveHighScore(newScore);
                }
                
                resetColor();
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
            }
                
            case 2:
                showInstructions();
                break;
                
            case 3:
                showHighScores();
                break;
                
            case 4:
                clearScreen();
                printHeader("CHANGE PLAYER NAME");
                setColor(YELLOW);
                cout << "\nCurrent name: " << playerName << endl;
                cout << "Enter new name: ";
                getline(cin, playerName);
                if (playerName.empty()) {
                    playerName = "Quiz Master";
                }
                setColor(GREEN);
                cout << "\nName changed to: " << playerName << endl;
                Sleep(1000);
                break;
                
            case 5:
                clearScreen();
                printHeader("THANK YOU FOR PLAYING!");
                setColor(YELLOW);
                cout << "\nGoodbye, " << playerName << "!" << endl;
                cout << "Hope you enjoyed the quiz game!" << endl;
                Sleep(2000);
                break;
                
            default:
                setColor(RED);
                cout << "Invalid choice! Please enter 1-5." << endl;
                Sleep(1000);
                break;
        }
        
    } while (choice != 5);
    
    return 0;
}
