# 🎇 Projeto: Controle de LEDs WS2812B com Raspberry Pi Pico

Este projeto implementa um sistema de controle para uma matriz de LEDs WS2812B usando a Raspberry Pi Pico. Através do código em C, utilizando a biblioteca PIO, é possível criar efeitos visuais animados como pisca-pisca, preenchimento progressivo e exibição de sprites.

## 🚀 Funcionalidades

- Controle de uma matriz 5x5 de LEDs WS2812B.
- Efeitos de animação, incluindo preenchimento progressivo e pisca-pisca.
- Uso do PIO (*Programável I/O*) da Raspberry Pi Pico para comunicação eficiente com os LEDs.
- Configuração e inicialização automática do sistema de LEDs.

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C
- **Microcontrolador:** Raspberry Pi Pico
- **Bibliotecas:** 
  - `pico/stdlib.h` (Biblioteca padrão do Raspberry Pi Pico)
  - `ws2818b.pio.h` (Código PIO para comunicação com os LEDs)

## 📜 Como Funciona

1. **Inicialização**: O código configura o sistema PIO e inicializa os LEDs em um estado desligado.
2. **Animação**: Diferentes efeitos visuais são aplicados, como:
   - Acendimento progressivo dos LEDs.
   - Exibição de padrões predefinidos (*sprites*).
   - Efeito pisca-pisca alternado.
3. **Loop Principal**: O código mantém a execução contínua, alternando os efeitos de iluminação.

## 🔧 Como Utilizar

### 1️⃣ Requisitos

- Raspberry Pi Pico
- LED Strip ou Matriz WS2812B (25 LEDs)
- Ambiente de desenvolvimento compatível com a Raspberry Pi Pico (SDK do Pico configurado)

### 2️⃣ Compilação e Upload

1. Clone este repositório:
   ```bash
   git clone https: //github.com/Davi-info/Show_de_Leds_BitDogLab.git
   cd seu-repositorio
2. Compile o código utilizando o SDK do Raspberry Pi Pico.
3. Envie o binário gerado para a Raspberry Pi Pico.

## 📌 Referências:
* 🎥 Vídeo explicativo: https://www.youtube.com/watch?v=chQdNiFmVm0
* 📜 Código base utilizado: Gist do Jonathas Jivago - https://gist.github.com/JonathasJivago/d61c6b6e5f44bdbe02df3e6fdd79754b
* 💡 BitDogLab (Placa utilizada nos testes): https://github.com/BitDogLab
