# Software Design Document: Digital Health Twin

**Version:** 1.0
**Status:** Draft
**Date:** 2025-12-16

---

## 1. Introduction

### 1.1. Purpose
Цель данного документа — предоставить детальное техническое описание системы "Цифровой Двойник Здоровья" для разработчиков и архитекторов.

### 1.2. Scope
Система включает в себя мобильное приложение для пользователей, облачный бэкенд для обработки данных, ML-сервисы для аналитики и интеграции с внешними источниками данных.

---

## 2. System Overview

Система построена на микросервисной архитектуре, развернутой в Kubernetes. Основной фокус сделан на масштабируемость (обработка потоков данных от миллионов устройств) и безопасность (шифрование медицинских данных).

---

## 3. Component Design

### 3.1. Data Ingestion Service
*   **Responsibility:** Прием и валидация данных с датчиков.
*   **Technology:** Go (Golang).
*   **Interface:** gRPC (для внутренних сервисов), HTTP/2 (для внешних клиентов).
*   **Data Flow:**
    1.  Получает пакет метрик.
    2.  Валидирует схему (JSON Schema).
    3.  Отправляет в Kafka (Topic: `raw-metrics`).
    4.  Сохраняет в InfluxDB (для быстрого доступа).

### 3.2. Processing Core
*   **Responsibility:** Бизнес-логика и оркестрация.
*   **Technology:** Python (FastAPI).
*   **Data Flow:**
    1.  Читает из Kafka.
    2.  Обогащает данными из PostgreSQL (профиль пользователя).
    3.  Вызывает ML Inference Service.
    4.  Генерирует рекомендации.
    5.  Отправляет уведомления через Firebase/APNS.

### 3.3. Biophysical Engine
*   **Responsibility:** Симуляция физиологических процессов.
*   **Technology:** Rust.
*   **Algorithm:** Система дифференциальных уравнений (ODE), описывающая кинетику глюкозы и инсулина.
*   **Integration:** Подключается к Python через FFI (PyO3) для максимальной производительности.

---

## 4. Database Design

### 4.1. PostgreSQL Schema (Metadata)

**Table: Users**
| Column | Type | Description |
| :--- | :--- | :--- |
| `id` | UUID | Primary Key |
| `email` | VARCHAR | Unique, Encrypted |
| `password_hash` | VARCHAR | Argon2 |
| `settings` | JSONB | User preferences |

**Table: Recommendations**
| Column | Type | Description |
| :--- | :--- | :--- |
| `id` | UUID | Primary Key |
| `user_id` | UUID | Foreign Key |
| `type` | ENUM | 'diet', 'activity', 'sleep' |
| `content` | TEXT | Recommendation text |
| `created_at` | TIMESTAMP | Creation time |

### 4.2. InfluxDB Schema (Time Series)

**Measurement: Biometrics**
*   **Tags:** `user_id`, `device_id`, `sensor_type`
*   **Fields:** `value` (float), `accuracy` (float)
*   **Retention Policy:** 1 year for raw data, infinite for downsampled (1h).

---

## 5. Deployment Strategy

*   **Environment:** Kubernetes (EKS/GKE).
*   **CI/CD:** GitHub Actions -> Helm Charts -> ArgoCD.
*   **Scaling:** Horizontal Pod Autoscaler (HPA) на основе CPU и метрик очереди Kafka (lag).
