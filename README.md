# 🛰️ Projeto Apollo-Grip: Sistema de Captura e Articulação Robótica Espacial

Este repositório contém o desenvolvimento completo de um subsistema de manipulação e captura robótica projetado para operar de forma totalmente funcional em ambientes gravitacionais reais. O projeto integra modelagem mecânica paramétrica de alta precisão desenvolvida no **OpenSCAD** e uma simulação eletroeletrônica interativa baseada na plataforma **Arduino Uno** via **Tinkercad**.

---

## 👥 Integrantes do Grupo

* **Victor Wittner** - RM: 98667
* **Matheus Haruo** - RM: 97663
* **João Saborido** - RM: 98184
* **Pedro Guerra de Souza Freitas** - RM: 99526

---

## 🛠️ Especificações do Sistema Eletrônico (Tinkercad)

O circuito foi projetado com foco na otimização da distribuição de energia e isolamento de ruídos eletromecânicos, utilizando uma lógica visual direta de estados para garantir a estabilidade operacional dos atuadores e do microcontrolador.

* **🔗 Link do Circuito Interativo:** [Acessar Simulação no Tinkercad](https://www.tinkercad.com/things/dq9RAbtXQdZ/editel?returnTo=%2Fdashboard)
* **⚡ Tensão de Operação do Circuito:** **5V (Corrente Contínua)**, alimentado de forma estabilizada e unificada entre os barramentos para suprir simultaneamente o microcontrolador Arduino e a demanda de corrente dos servomotores sob carga.

### 📋 Mapeamento de Pinos e Conexões
* **Pino Digital 6:** Saída Digital - LED Vermelho (Status: Mecanismo Fechado / Carga Presa)
* **Pino Digital 9:** Sinal PWM - Servo Motor 1 (Articulação / Elevação do Braço)
* **Pino Digital 10:** Sinal PWM - Servo Motor 2 (Atuação do Mecanismo de Captura da Garra)
* **Pino Digital 13:** Saída Digital - LED Verde (Status: Mecanismo Aberto / Pronto para Captura)

### 🕹️ Interface de Controle Serial e Lógica de Operação
O firmware processa comandos via terminal serial (configurado a 9600 bps) para movimentação dinâmica e atualização instantânea dos indicadores visuais (LEDs):
* `U` (Up): Eleva o braço articulado em passos de 15° (Limite máximo de proteção: 180°).
* `D` (Down): Abaixa o braço articulado em passos de 15° (Limite mínimo de proteção: 0°).
* `O` (Open): Abre a garra (posição de recuo a 10°), ativa o indicator LED Verde e desliga o LED Vermelho.
* `C` (Close): Fecha a garra (posição de pressão a 90°), ativa o indicador LED Vermelho e desliga o LED Verde.

---

## 📐 Engenharia Mecânica e Modelagem 3D Modular (OpenSCAD)

Toda a estrutura e os componentes móveis da garra foram desenvolvidos utilizando o software **OpenSCAD**, aplicando modelagem geométrica puramente paramétrica por código. Atendendo a requisitos de manutenibilidade e modularidade industrial, **a garra foi dividida em duas partes independentes que se acoplam mecanicamente via encaixe macho-fêmea (chaveta)**.

### ⚙️ Características Mecânicas Implementadas
* **Mecanismo de Inversão por Engrenagem:** Otimização estrutural para operar com apenas **1 servomotor ativo** na ponta do braço. O dente esquerdo transmite o torque diretamente para o dente direito através de uma coroa dentada síncrona de **18 dentes**, garantindo simetria absoluta de movimento e eliminando folgas mecânicas (*backlash*). A distância teórica calculada entre os eixos de fixação no chassi para o acoplamento perfeito é de **22.6 mm**.
* **Acoplamento Direto:** A base de rotação possui geometria e rebaixo central de 4.2 mm para encaixe estrito do eixo estriado do microsservo SG90, além de furação guia auxiliar para parafusos M2 (distanciados a 10 mm) para fixação direta do flange/horn do motor.
* **Geometria Manifold Perfeita:** Malha 3D corrigida utilizando técnicas de interseção estrita (*overlapping*), gerando sólidos fechados ("estanques"), livres de erros de faces abertas ou cascas flutuantes, garantindo compatibilidade direta com fatiadores (como Ultimaker Cura ou PrusaSlicer).
* **Alívio de Massa Aeroespacial:** Perfurações internas distribuídas ao longo das hastes baseadas em princípios de alívio estrutural, reduzindo o momento de inércia e o peso sobre os motores sob efeito da gravidade sem comprometer a rigidez de torção do componente.

### 🖨️ Instruções para Geração dos Arquivos 3D (.STL)
O arquivo `.scad` unifica o projeto mecânico de forma condicional. Para visualizar e exportar cada componente separadamente para a impressão 3D, localize a variável **`peca_para_gerar`** (próxima à linha 8 do script) e alterne seu valor numérico antes de renderizar:

1. **Para gerar a Engrenagem da Base (Com encaixe Fêmea):**
   * Configure `peca_para_gerar = 1;`
   * Pressione **F6** para processar a malha e exporte como `apollo_engrenagem_base.stl`.
2. **Para gerar a Haste da Pinça (Com encaixe Macho):**
   * Configure `peca_para_gerar = 2;`
   * Pressione **F6** para processar a malha e exporte como `apollo_haste_pinca.stl`.

---

## 📁 Estrutura de Diretórios Recomendada

* `/src` : Firmware fonte do Arduino (`.ino`).
* `/cad` : Modelagem paramétrica no OpenSCAD (`.scad`) e arquivos de malha separados para impressão (`.stl`).
* `/docs` : Imagens do circuito montado no Tinkercad e capturas de tela do render mecânico.
