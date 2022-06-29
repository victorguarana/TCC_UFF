# TCC_UFF
Trabalho de conclusão de curso

---
## Critérios para calcular rota:

### Algoritmo Guloso:

- A rota será calculada considerando que nenhum dos veiculos podem ficar sem combustível em nenhuma cenário.
- O próximo cliente é escolhido selecionando o cliente mais próximo a partir da posição atual, além disso:
    - O carro só se dirige para o próximo cliente caso consiga realizar a entrega, e retornar para algum depósito. Caso não consiga, ele deve visitar o depósito mais próximo da posição atual.
    - O drone só se dirige para o próximo cliente caso consiga realizar a entrega, e retornar ao próximo ponto do carro que ele está vinculado. Caso não consiga, ele deve voltar imediatamente para o carro.


### Algoritmo de Busca Local:

- Com uma rota pronta, oinicialmente o algoritmo fará uma busca para encontrar o cliente que tem um maior custo local para ambos os veiculos.
- O custo de uma parada é calculado utilzando somando as distancias dos ponto atual para os pontos vizinhos.
- Após a definição dos clientes mais custosos, vai ocorrer um swap entre os clientes seguindo os seguintes passos:
    1. Remove a parada do drone;
    2. Remove a parada do carro;
    3. Insere o cliente, que antes era entregue pelo drone, na rota do carro, onde o custo total da rota é a menor possível;
    4. Insere o cliente, que antes era entregue pelo carro, na rota do drone, onde o custo total da rota é a menor possível;

---

## Propriedades

|                     | Carro | Drone |
|---------------------|:-----:|:-----:|
| Capacidade de Carga | 500   | 10    |
| Alcance total       | 1000  | 100   |
| Velocidade          | 10    | 25    |

## Considerações:
- O tempo de recarga e reabastecimento dos veiculos é instantâneo.
- O Custo total da rota é calculado somando todos os tempos de entregas (Considerando entregas paralelas).


### Próximos estudos
- Drones podem decolar em um veiculo e retornar e outro.
