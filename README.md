Simple String Matching Chatbot

📖 Overview
This project implements a **simple chatbot system** using fundamental string matching algorithms. It demonstrates the practical application of **Brute Force** and **Knuth-Morris-Pratt (KMP)** algorithms for keyword detection and response generation. The chatbot is designed as an educational tool to showcase algorithm efficiency, file handling, and modular programming concepts.

---

Features
- Implements **Brute Force** and **KMP** string matching algorithms.
- Case-insensitive keyword detection.
- File-based response database (`responses.txt`) for easy updates.
- Command-line interface for user interaction.
- Performance comparison between algorithms.
- Extensible architecture for future enhancements.

---

Algorithms
Brute Force
- Checks the pattern at every possible position in the text.
- **Time Complexity:** O(n × m)  
- **Space Complexity:** O(1)

Knuth-Morris-Pratt (KMP)
- Uses preprocessing with the **Longest Prefix Suffix (LPS)** array.
- **Time Complexity:** O(n + m)  
- **Space Complexity:** O(m)

---

📂 Project Structure
string-matching-chatbot/ │ ├── src/                     # Source code (C++) │   └── chatbot.cpp ├── responses.txt            # Keyword-response database ├── Project Report Final.pdf # Detailed project report ├── README.md                # Project documentation └── LICENSE                  # Optional license file

---

Usage
1. Compile the chatbot:
   ```bash
   g++ chatbot.cpp -o chatbot


- Run the chatbot:
./chatbot
- Interact with the chatbot:
- Type greetings like hello, hi, or bye.
- Ask questions such as what's your name? or how are you?.
- Type quit to exit.
- 📊 Performance Evaluation- Short inputs (10 chars): Comparable performance between Brute Force and KMP.
- Medium inputs (100 chars): KMP shows ~58% improvement.
- Long inputs (1000 chars): KMP achieves ~88% faster processing.
  Future Improvements- Add fuzzy matching for spelling variations.
- Machine learning-based response generation.
- Multi-language support.
- Graphical User Interface (GUI).
- 👨‍💻 Author: Md. Lion Mia - B.Sc. in Computer Science and Engineering, Teesta University
- Competitive programmer & IT Support Specialist.
- Email: rjleon.lk@gmail.com
- References- Introduction to Algorithms – Cormen et al.
  Knuth, Morris, Pratt (1977) – Fast Pattern Matching in Strings
  Gusfield (1997) – Algorithms on Strings, Trees, and Sequences

