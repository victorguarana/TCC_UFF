# TO DO LIST
#### Implementação da rota hibrida:
- [ ] Inicialmente construir uma rota com algoritmo guloso utilizando apenas os carros.
- [ ] A partir deste ponto, utilizar um algoritmo guloso (?) para substituir entregas de carro por entregas de drones.
- [ ] Depois seguir com as perturbações.

#### Definir qualidade 
- [ ] Utilizar o tempo como indicador de qualidade.

#### Tipos de operações de pertubação (Podem ser feitas mais de uma por vez (?) ):
- [ ] Trocar entrega de veiculo por entrega de drone ( e vice versa (?) ).
- [ ] Trocar ordem de entregas.
- [ ] Verificar se alteração continua com boa qualidade.

#### Pontos extras:
- [ ] Verificar como melhorar a manipulação dos arrays.
- [ ] Adicionar peso da carga na estrutura do cliente (E utilizar como criterio de validação da rota).
- [ ] Adicionar combustivel/carga ao veiculos.
    - [ ] Adicionar metodos para simular o consumo dos mesmos.
    - [ ] Adicionar método para simular a recarga dos drones.
- [ ] Adicionar "relação" entre as classes de carro e drone (Ex: Car has many drones).