#include <stdio.h>
#include "pico/stdlib.h"


// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin) {
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite() {
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Função para converter a posição da matriz para uma posição do vetor.
int getIndex(int x, int y) {
    if (y % 2 == 0) {
        return 24-(y * 5 + x); // Linha par (esquerda para direita).
    } else {
        return 24-(y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
    }
}

// Função de animação (acendendo LEDs um por vez)
void lightUpSprite(int sprite[5][5][3], int speed) {
  for (int i = 0; i < 25; i++) {
    int x = i % 5;
    int y = i / 5;
    int posicao = getIndex(x, y);
    npSetLED(posicao, sprite[x][y][0], sprite[x][y][1], sprite[x][y][2]);
    npWrite();
    sleep_ms(speed);
  }
}

// Função para o efeito "pisca-pisca" movimentando LEDs
void blinkEffect() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int posicao = getIndex(i, j);
      // Acende o LED com uma cor alternada
      if ((i + j) % 2 == 0) {
        npSetLED(posicao, 255, 0, 0);  // LED vermelho
      } else {
        npSetLED(posicao, 0, 0, 255);  // LED azul
      }
    }
    npWrite();
    sleep_ms(200);  // Aguarda um pouco para o efeito
  }
}


int sprite1[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},    
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};


int sprite2[5][5][3] = {
  {{0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}},
  {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}}
};


int sprite3[5][5][3] = {
  {{255, 255, 0}, {0, 255, 0}, {255, 0, 0}, {0, 0, 255}, {255, 255, 0}},
  {{0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 0}, {0, 255, 0}},
  {{255, 0, 0}, {0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 0}},
  {{0, 0, 255}, {255, 0, 0}, {0, 255, 0}, {255, 255, 0}, {0, 0, 255}},
  {{255, 255, 0}, {0, 255, 0}, {255, 0, 0}, {0, 0, 255}, {255, 255, 0}}
};


int matriz[5][5][3] = {
    {{0, 0, 0}, {239, 23, 23}, {0, 0, 0}, {239, 23, 23}, {0, 0, 0}},    
    {{239, 23, 23}, {0, 0, 0}, {239, 23, 23}, {0, 0, 0}, {239, 23, 23}},
    {{239, 23, 23}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {239, 23, 23}},    
    {{0, 0, 0}, {239, 23, 23}, {0, 0, 0}, {239, 23, 23}, {0, 0, 0}},    
    {{0, 0, 0}, {0, 0, 0}, {239, 23, 23}, {0, 0, 0}, {0, 0, 0}}
};

int main() {
  stdio_init_all();
  npInit(LED_PIN);
  npClear();

  while (true) {
    // Animação 1: Acendendo LEDs progressivamente
    lightUpSprite(sprite1, 100);  // Mais rápido
    npClear();
    npWrite();
    sleep_ms(500);

 
    for (int linha = 0; linha < 5; linha++) {
      for (int coluna = 0; coluna < 5; coluna++) {   
      
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, matriz[coluna][linha][0], matriz[coluna][linha][1], matriz[coluna][linha][2]);
      }
    }
    npWrite();
    sleep_ms(500);
  
    lightUpSprite(matriz, 100);
    npClear();
    npWrite();
    sleep_ms(500);
 

    lightUpSprite(sprite3, 100);
    npClear();
    npWrite();
    sleep_ms(500);
    

 
    blinkEffect();
    npClear();
    npWrite();
    sleep_ms(500);
  }
}
