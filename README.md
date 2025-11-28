# Box Counter Challenge

Desenvolvido durante o 2º período da graduação em Sistemas de Informação.

## Descrição

Box Counter Challenge é um jogo de agilidade visual e mental onde o objetivo principal é contar com precisão o número de caixas exibidas na tela durante um período limitado de tempo.

### Funcionamento do Jogo

O jogo apresenta rodadas consecutivas onde um conjunto de caixas é mostrado no centro da tela. Estas caixas permanecem visíveis apenas por um curto período, que diminui progressivamente a cada rodada completada com sucesso. Simultaneamente, o número total de caixas aumenta gradualmente, tornando a contagem mais desafiadora.

Cada jogador inicia a partida com 5 vidas. Após as caixas desaparecerem da tela, o jogador dispõe de exatos 3 segundos para inserir seu palpite sobre quantas caixas foram exibidas.

### Sistema de Pontuação

- **100 pontos**: atribuídos quando o jogador acerta exatamente o número de caixas
- **50 pontos**: concedidos quando o jogador erra por apenas uma caixa (para mais ou para menos)
- **Perda de vida**: ocorre a cada erro, independentemente da margem de erro

O jogo é finalizado quando o jogador perde todas as suas 5 vidas.

### Ranking e Armazenamento

O sistema mantém um registro das 10 maiores pontuações alcançadas. Se um jogador obtiver uma pontuação que se classifique entre as 10 melhores, seu nome e pontuação serão automaticamente salvos no arquivo de recordes.

### Modos de Jogo

- **Single Player**: um jogador desafia suas próprias habilidades
- **Multiplayer**: dois jogadores competem simultaneamente na mesma tela, contando as mesmas caixas mas inserindo seus palpites independentemente

## Controles

### Jogador 1
- Tecla **W**: incrementa o número do palpite (aumenta a contagem)
- Tecla **S**: decrementa o número do palpite (diminui a contagem)

### Jogador 2
- Tecla **Seta para Cima**: incrementa o número do palpite (aumenta a contagem)
- Tecla **Seta para Baixo**: decrementa o número do palpite (diminui a contagem)

## Tecnologias Utilizadas

- Linguagem de programação C
- Biblioteca Raylib para renderização gráfica e manipulação de áudio

## Desenvolvido por

- [Yan Neves](https://github.com/yan-dhsk)
- [Vinicius Meneses](https://github.com/viniciusmeneses-tech)
