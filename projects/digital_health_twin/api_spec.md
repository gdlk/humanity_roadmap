# API Specification: Digital Health Twin

**Version:** 1.0.0
**Protocol:** REST (HTTP/2) + WebSocket
**Base URL:** `https://api.health-twin.global/v1`

---

## 1. Authentication

Все запросы должны содержать заголовок `Authorization: Bearer <token>`.

## 2. Endpoints

### 2.1. User Profile

#### `GET /user/profile`
Получение профиля текущего пользователя.

**Response:**
```json
{
  "id": "uuid",
  "name": "John Doe",
  "age": 35,
  "height": 180,
  "weight": 75,
  "chronic_conditions": ["asthma"]
}
```

#### `PUT /user/profile`
Обновление данных профиля.

### 2.2. Health Data (Ingestion)

#### `POST /data/metrics`
Загрузка пакета метрик с носимых устройств.

**Request:**
```json
{
  "device_id": "apple_watch_s10",
  "metrics": [
    {
      "type": "heart_rate",
      "value": 72,
      "timestamp": "2026-05-20T10:00:00Z"
    },
    {
      "type": "steps",
      "value": 150,
      "timestamp": "2026-05-20T10:05:00Z"
    }
  ]
}
```

### 2.3. Recommendations

#### `GET /recommendations/current`
Получение актуальных рекомендаций от ИИ.

**Response:**
```json
{
  "items": [
    {
      "id": "rec_123",
      "type": "activity",
      "priority": "high",
      "message": "Ваш уровень глюкозы повышается. Рекомендуется 15-минутная прогулка.",
      "created_at": "2026-05-20T10:10:00Z"
    }
  ]
}
```

### 2.4. Real-time Stream

#### `WS /stream`
WebSocket соединение для получения алертов в реальном времени.

**Events:**
*   `alert`: Критическое изменение показателей.
*   `sync_status`: Статус синхронизации данных.
