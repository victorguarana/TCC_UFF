# TO DO LIST
#### Implementação da rota hibrida:
- [X] Inicialmente construir uma rota com algoritmo guloso utilizando apenas os carros.
- [X] A partir deste ponto, utilizar um algoritmo guloso para substituir entregas de carro por entregas de drones.
- [X] Depois seguir com as perturbações.
- [X] Considerar as cargas dos drones dentro da carga total do carro.

#### Implementação do ILS:
- [X] Validar as alterações na rota (Antes ou depois da inserção?)

#### Definir qualidade:
- [X] Utilizar o tempo como indicador de qualidade.
- [X] Calcular qualidade da rota.
- [ ] Durante entregas simultâneas, ignorar a rota de menor tempo.

#### Tipos de operações de pertubação (Podem ser feitas mais de uma por vez (?) ):
- [X] Fazer Swap das piores entregas de cada veiculo.
- [X] Transformar parada de drone em parada de carro.
- [ ] Remover ou alterar as posições dos depósitos nas rotas.
- [X] Verificar se alteração continua com boa qualidade.

#### Pontos extras:
- [X] Verificar como melhorar a manipulação dos arrays.
- [X] Adicionar peso da carga na estrutura do cliente (E utilizar como criterio de validação da rota).
- [X] Adicionar combustivel/carga ao veiculos.
    - [X] Adicionar metodos para simular o consumo dos mesmos.
    - [X] Adicionar método para simular a recarga dos drones.
- [X] Adicionar "relação" entre as classes de carro e drone (EX: Car has many drones).
- [ ] Remover a necessidade do vôo terminar no carstop seguinte.
- [ ] Adicionar validação (somente de peso) no método que procura um carstop para transformar em dronestop

#### Validador de rota:
- [X] Implementar uma função dentro de veiculos para receber a classe de cliente e a posição atual e verificar, de acordo com os atributos do veiculo, se é possivel fazer a entrega.

#### Múltiplos Carros:
- [X] Refatorar para a rota pertencer ao carro.

#### Outras ideias:
- [ ] Drones podem decolar em um veiculo e retornar e outro.
- [ ] Adicionar uma margem abaixo do limite dos veiculos no algotimo guloso.
