# Quiz-Game
# 🎯 Quiz Game — C++ Console Game

A colorful, feature-rich console-based quiz game built in C++. Test your knowledge across multiple categories with timed questions, difficulty levels, and a high score system!

---

## 🎮 Features

- **Two Quiz Types** — Multiple Choice (MCQ) and True/False
- **3 Categories** — General Knowledge, Mathematics, Science
- **3 Difficulty Levels** — Easy, Medium, Hard
- **Timed Questions** — 15 seconds for MCQ, 10 seconds for True/False
- **Animated Text** — Colorful console output with character-by-character animation
- **High Score System** — Scores saved and displayed after each game
- **Grade Feedback** — Get rated: Excellent / Good / Fair / Needs Improvement
- **Player Name** — Personalized experience with name change option

---

## 🖥️ Screenshots
<img width="473" height="161" alt="image" src="https://github.com/user-attachments/assets/4c730556-8c7a-41a0-b4c9-7bee001cc1b0" />
<img width="660" height="302" alt="image" src="https://github.com/user-attachments/assets/0c8c2e7e-fc7b-492c-be27-2ec1516f26b2" />
<img width="578" height="290" alt="image" src="https://github.com/user-attachments/assets/0a0c2f13-13fc-4b53-aff2-87eff75a2dc8" />
<img width="555" height="291" alt="image" src="https://github.com/user-attachments/assets/a2b4a338-fd5c-43ac-92ad-2eccf65aaecc" />
<img width="550" height="306" alt="image" src="https://github.com/user-attachments/assets/bb60ef30-af6a-472a-897d-77a1dd32cd93" />
<img width="1041" height="235" alt="image" src="https://github.com/user-attachments/assets/30d7d90a-cb07-4622-8a16-048912549336" />
<img width="856" height="340" alt="image" src="https://github.com/user-attachments/assets/922e5a3f-271f-4351-a3be-430fb4f02b03" />
<img width="889" height="452" alt="image" src="https://github.com/user-attachments/assets/8d0e12a2-0808-4779-9e00-82bb574962fd" />
<img width="1078" height="417" alt="image" src="https://github.com/user-attachments/assets/7aab55de-f300-4bc1-8983-2dab6f183fcc" />


---

## 🚀 How to Run

### Requirements
- Windows OS
- Dev-C++ / Code::Blocks / any C++ compiler (MinGW)

### Steps
1. Clone or download this repository
2. Open `Quiz_Game.cpp` in Dev-C++ or Code::Blocks
3. Compile and Run (`F11` in Dev-C++)

> ⚠️ This game uses Windows-only headers (`windows.h`, `conio.h`) so it only runs on Windows.

---

## 🗂️ How to Play

1. Enter your player name
2. Choose from the main menu:
   - **Start New Quiz** — Pick quiz type, category, and difficulty
   - **View Instructions** — Learn the rules
   - **View High Scores** — See top scores
   - **Change Player Name**
3. Answer questions before time runs out!
4. See your final score and grade

---

## 📊 Scoring System

| Difficulty | Points per Question |
|------------|-------------------|
| Easy       | 10 points         |
| Medium     | 20 points         |
| Hard       | 30 points         |

| Percentage | Grade              |
|------------|--------------------|
| 80%+       | ⭐ Excellent        |
| 60–79%     | ✅ Good Job         |
| 40–59%     | 🟡 Fair             |
| Below 40%  | 🔴 Needs Improvement|

---

## 🛠️ Tech Stack

- **Language:** C++
- **Compiler:** Dev-C++ (MinGW)
- **Libraries:** `iostream`, `vector`, `ctime`, `fstream`, `windows.h`, `conio.h`

---

## 💡 OOP & C++ Concepts Used

- Structs (`Question`, `PlayerScore`)
- Vectors (`vector<Question>`, `vector<PlayerScore>`)
- Enums (color codes)
- Functions with parameters and return values
- File I/O (`fstream`) for saving high scores
- String manipulation
- Timer logic using `ctime`

---

## 👨‍💻 Author

**Abdullah Arqam**  
BS Artificial Intelligence — HITEC University, Taxila Cantt  
🔗 [LinkedIn](www.linkedin.com/in/abdullah-arqam-9200a1404) | 📧 abdullaharqam67@gmail.com

---

## 📄 License

This project is open source and free to use for learning purposes.
