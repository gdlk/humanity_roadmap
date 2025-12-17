# Архитектура AtomPhys

## Обзор системы
AtomPhys построен по модульной архитектуре, разделяющей вычисления физики, управление состоянием и рендеринг.

```mermaid
graph TD
    User[Пользователь / Genesis IDE] --> API[AtomPhys API]
    API --> Core[Simulation Core]
    
    subgraph "Simulation Core"
        Integrator[Time Integrator]
        ForceField[Force Field Calculator]
        QuantumSolver[Quantum Solver (DFT)]
        NeighborList[Neighbor List Manager]
    end
    
    Core --> State[State Manager]
    State --> GPU[GPU/QPU Acceleration]
    
    ForceField --> Potentials[Potentials Library]
    QuantumSolver --> QuantumLib[Quantum Effects Lib]
```

## Основные модули

### 1. Simulation Core (Ядро симуляции)
Центральный компонент, управляющий циклом симуляции.
*   **Time Integrator:** Отвечает за численное интегрирование уравнений движения (Verlet, Leapfrog).
*   **Neighbor List Manager:** Оптимизирует вычисления, отслеживая списки соседей для каждого атома (Verlet lists, Cell lists).

### 2. Force Field Calculator (Калькулятор силовых полей)
Вычисляет силы, действующие на каждый атом в классическом приближении.
*   **Bonded Interactions:** Растяжение связей, углы, торсионные углы.
*   **Non-bonded Interactions:** Ван-дер-Ваальс (Lennard-Jones), Кулон (Electrostatics).

### 3. Quantum Solver (Квантовый решатель)
Подключается для областей, требующих высокой точности (разрыв/образование связей).
*   Использует приближенные методы DFT (Density Functional Theory) или Tight-Binding для ускорения.
*   Работает только в локальных "активных зонах" (Active Zones).

### 4. State Manager (Менеджер состояния)
Хранит текущее состояние системы:
*   Координаты (x, y, z)
*   Импульсы (px, py, pz)
*   Типы атомов и заряды
*   Топология связей

### 5. Hardware Acceleration Layer (HAL)
Абстракция над железом.
*   **CUDA/ROCm Backend:** Для классической MD.
*   **QPU Backend:** Экспериментальный интерфейс для квантовых процессоров (для решения уравнения Шредингера).

## Поток данных (Data Flow)

1.  **Инициализация:** Загрузка начальной конфигурации атомов и параметров силового поля.
2.  **Шаг симуляции:**
    *   Обновление списков соседей (если нужно).
    *   Вычисление сил (Классика + Кванты).
    *   Интегрирование уравнений движения (обновление координат и скоростей).
    *   Применение термостата/баростата.
3.  **Вывод:** Передача нового состояния в API для визуализации или анализа.