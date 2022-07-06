# TO DO LIST
#### Implementação da rota hibrida:
- [X] Inicialmente construir uma rota com algoritmo guloso utilizando apenas os carros.
- [X] A partir deste ponto, utilizar um algoritmo guloso para substituir entregas de carro por entregas de drones.
- [X] Depois seguir com as perturbações.
- [X] Considerar as cargas dos drones dentro da carga total do carro.

#### Implementação do ILS:
- [X] Validar as alterações na rota (Antes ou depois da inserção?)
- [ ] Cancelar operação ou find quando não existir stops.

#### Definir qualidade:
- [X] Utilizar o tempo como indicador de qualidade.
- [X] Calcular qualidade da rota.
- [X] Durante entregas simultâneas, ignorar a rota de menor tempo.

#### Tipos de operações de pertubação (Podem ser feitas mais de uma por vez (?) ):
- [X] Fazer Swap das piores entregas de cada veiculo.
- [X] Transformar parada de drone em parada de carro.
- [X] Verificar se alteração continua com boa qualidade.

#### Pontos extras:
- [X] Verificar como melhorar a manipulação dos arrays.
- [X] Adicionar peso da carga na estrutura do cliente (E utilizar como criterio de validação da rota).
- [X] Adicionar combustivel/carga ao veiculos.
    - [X] Adicionar metodos para simular o consumo dos mesmos.
    - [X] Adicionar método para simular a recarga dos drones.
- [X] Adicionar "relação" entre as classes de carro e drone (EX: Car has many drones).
- [X] Remover a necessidade do vôo terminar no carstop seguinte.
- [X] Adicionar validação (somente de peso) no método que procura um carstop para transformar em dronestop

#### Validador de rota:
- [X] Implementar uma função dentro de veiculos para receber a classe de cliente e a posição atual e verificar, de acordo com os atributos do veiculo, se é possivel fazer a entrega.

#### Múltiplos Carros:
- [X] Refatorar para a rota pertencer ao carro.

#### Múltiplos Drones:
- [X] Refatorar modelos
- [X] Refatorar Greedy
- [ ] Considerar multiplos delays de voos durante calculo de custo
- [ ] Refatorar ILS

#### Outras ideias:
- [ ] Adicionar uma margem abaixo do limite dos veiculos no algotimo guloso.
