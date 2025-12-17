# AtomPhys API Reference

## C++ Core API

### `System`
Класс, представляющий физическую систему.

```cpp
class System {
public:
    // Инициализация
    void addAtom(int type, double mass, double charge, Vec3 position);
    void setBox(Vec3 dimensions); // Периодические граничные условия

    // Управление симуляцией
    void setIntegrator(std::shared_ptr<Integrator> integrator);
    void addForceField(std::shared_ptr<ForceField> ff);
    
    // Шаг по времени
    void step(double dt);
    
    // Доступ к данным (Zero-copy)
    std::span<Vec3> getPositions();
    std::span<Vec3> getVelocities();
    std::span<Vec3> getForces();
};
```

### `ForceField`
Базовый класс для всех взаимодействий.

```cpp
class ForceField {
public:
    virtual void compute(System& sys) = 0;
    virtual double getEnergy() const = 0;
};
```

---

## Python API (pybind11)

### `atomphys.System`

```python
import atomphys

# Создание системы
sys = atomphys.System()
sys.box = [10.0, 10.0, 10.0]  # Нанометры

# Добавление атомов
sys.add_atom(type=1, mass=12.01, charge=0.0, pos=[0, 0, 0]) # Углерод
sys.add_atom(type=1, mass=12.01, charge=0.0, pos=[0.14, 0, 0])

# Настройка взаимодействий
lj = atomphys.LennardJones(epsilon=0.1, sigma=0.34)
sys.add_force_field(lj)

# Запуск симуляции
integrator = atomphys.VelocityVerlet(dt=0.001) # 1 фс
sys.integrator = integrator

for i in range(1000):
    sys.step()
    if i % 100 == 0:
        print(f"Step {i}, Energy: {sys.energy}")