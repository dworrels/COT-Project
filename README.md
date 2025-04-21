# 🤖 Probabilistic Finite-State Chatbot

A lightweight keyword-driven chatbot built in C++ that uses probabilistic finite-state automata to generate varied responses. Designed to simulate online customer service interactions, such as shipping and order inquiries, similar to support systems used by companies like Amazon.

---

## Features

- Custom state machine built with a `stateNode` structure
- Keyword-based input recognition (e.g., "order", "update", "start")
- Randomized response generation using `rand()` for dynamic interaction
- Tree-based organization of chatbot states
- Terminal interface with continuous conversation loop
- Fallback responses for unrecognized inputs

---

## 🧠 How It Works

1. **User Input** is parsed into individual lowercase words.
2. **Keyword Matching** checks input against known keywords.
3. If a match is found:
   - The chatbot transitions to the corresponding `stateNode`.
   - It selects one of three pre-written responses **randomly**.
4. If no match:
   - A fallback message prompts the user to rephrase.

---

EXAMPLE INTERACTION
> Please enter your statement:
I want to update my order

Bot: What is your order number?

