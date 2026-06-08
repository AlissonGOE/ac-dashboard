# AC Monitor — Assetto Corsa Telemetry Dashboard

## Descrição

Sistema de telemetria em tempo real para Assetto Corsa desenvolvido em C. Lê dados da shared memory do jogo, exibe no terminal via menu interativo e envia via serial para um ESP32 que controla um display LCD com dashboard de corrida e um LED RGB de shiftlight dinâmico.

---

## Arquitetura

```
[Assetto Corsa]
      |
      | Shared Memory (Windows API)
      |
[PC - AC Monitor em C]
      |
      | USB Serial (115200 baud)
      |
[ESP32-S3]
      |
      |--- Display LCD  →  Dashboard de corrida
      |--- LED RGB      →  Shiftlight dinâmico
```

---

## Funcionalidades

### PC (Windows)
- Leitura da shared memory do Assetto Corsa (`acpmf_physics`, `acpmf_static`, `acpmf_graphics`)
- Menu interativo com grupos de telemetria
- Atualização em tempo real no terminal
- Envio de telemetria via serial para o ESP32
- Dois modos de envio — Dashboard e Shiftlight

### Grupos de telemetria disponíveis
- **Motor** — RPM, velocidade, marcha, acelerador, freio, turbo, ABS, TC
- **Pneus** — pressão, temperatura, desgaste, slip, camber
- **Suspensão** — travel, ride height, centro de gravidade
- **Carroceria** — danos, roll, pitch, heading, G forces
- **Sessão** — volta, posição, tempos, combustível, pit lane
- **Veículo** — dados estáticos do carro e pista

### ESP32
- Recebe telemetria via UART (USB Serial)
- **Modo Dashboard** — exibe dados de corrida no display LCD em tempo real
- **Modo Shiftlight** — controla LED RGB com gradiente de cor baseado no percentual de RPM

### Dashboard LCD
- Posição e volta atual
- RPM e marcha
- Velocidade e freio
- Combustível e consumo por volta
- Tempos de volta
- Temperatura e desgaste dos pneus
- Nível de ABS e controle de tração

---

## Tecnologias

| Camada | Tecnologia |
|---|---|
| PC | C (GCC/MinGW), Windows API |
| Comunicação | Serial UART 115200 baud |
| Firmware | ESP-IDF v6, FreeRTOS |
| Display | LCD via ESP32 |
| Shiftlight | LED RGB WS2812 |

---

## Estrutura do Projeto

```
AC_TELEMETRIES/          # Projeto PC
├── ac_types.h           # Structs da shared memory
├── main.c
├── shared_memory/
│   ├── header/
│   │   └── shared_memory.h
│   └── source/
│       └── shared_memory.c
├── telemetria/
│   ├── header/
│   │   ├── motor.h
│   │   ├── pneus.h
│   │   ├── suspensao.h
│   │   ├── carroceria.h
│   │   ├── auxiliares.h
│   │   ├── sessao.h
│   │   └── veiculo.h
│   └── source/
│       ├── motor.c
│       ├── pneus.c
│       ├── suspensao.c
│       ├── carroceria.c
│       ├── auxiliares.c
│       ├── sessao.c
│       └── veiculo.c
├── ui/
│   ├── header/
│   │   ├── menu.h
│   │   └── shiftlight.h
│   └── source/
│       ├── menu.c
│       └── shiftlight.c
└── serial/
    ├── header/
    │   └── serial.h
    └── source/
        └── serial.c

AC_DASHBOARD/            # Projeto ESP32
└── main/
    ├── main.c
    ├── telemetry.h
    ├── telemetry.c
    ├── shiftlight.h
    └── shiftlight.c
```

---

## Protocolo Serial

Os dados são enviados em uma única linha com campos separados por `|` e terminando em `\n`:

```
MOD:DASH|POS:3|LAP:5|NLAP:30|FUEL:45.2|MXF:120.0|FPV:2.10|RPM:6500|MXR:8750|GER:3|SPD:120.5|BRK:0|CTIM:1:32.541|BTIM:1:31.998|TT0:85.2|TT1:86.1|TT2:82.3|TT3:83.5|TW0:98.1|TW1:97.8|TW2:99.0|TW3:98.5|ABS:0.12|TC:0.10
MOD:SHIFT|RPM:6500|MXR:8750
```

### Legenda dos campos

| Campo | Descrição |
|---|---|
| MOD | Modo — DASH ou SHIFT |
| POS | Posição na corrida |
| LAP | Volta atual |
| NLAP | Total de voltas |
| FUEL | Combustível atual (L) |
| MXF | Combustível máximo (L) |
| FPV | Consumo por volta (L) |
| RPM | Rotação atual |
| MXR | RPM máximo |
| GER | Marcha (0=R, 1=N, 2+=marchas) |
| SPD | Velocidade (km/h) |
| BRK | Freio (%) |
| CTIM | Tempo da volta atual |
| BTIM | Melhor tempo |
| TT0-3 | Temperatura pneus FL/FR/RL/RR (°C) |
| TW0-3 | Desgaste pneus FL/FR/RL/RR (%) |
| ABS | Nível ABS |
| TC | Nível controle de tração |

---

## Como compilar — PC

### Pré-requisitos
- GCC (MinGW ou MSYS2)
- Assetto Corsa instalado via Steam

### Compilar

```bash
gcc -I. main.c \
    shared_memory/source/shared_memory.c \
    telemetria/source/motor.c \
    telemetria/source/pneus.c \
    telemetria/source/suspensao.c \
    telemetria/source/veiculo.c \
    telemetria/source/carroceria.c \
    telemetria/source/sessao.c \
    telemetria/source/auxiliares.c \
    ui/source/menu.c \
    ui/source/shiftlight.c \
    serial/source/serial.c \
    -o ac_telemetria
```

### Executar
1. Abrir o Assetto Corsa e entrar em uma sessão
2. Rodar `ac_telemetria.exe`
3. Navegar pelo menu com os números

---

## Como compilar — ESP32

### Pré-requisitos
- ESP-IDF v6.0+
- ESP32-S3

### Compilar e gravar
```bash
idf.py build
idf.py flash monitor
```

---

## Shiftlight

O LED RGB do ESP32-S3 indica o percentual de RPM em relação ao RPM máximo do carro:

| Percentual | Cor |
|---|---|
| 0% — 60% | Verde |
| 60% — 85% | Verde → Amarelo (gradiente) |
| 85% — 95% | Amarelo → Vermelho (gradiente) |
| 95%+ | Pisca branco — SHIFT! |

---

## Motivação

Projeto desenvolvido para unir três áreas de estudo simultâneas:

- Estruturas de dados em C (disciplina acadêmica)
- Programação de sistemas embarcados (área profissional)
- Paixão por simuladores de corrida
