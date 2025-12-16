# Mobile App Development Plan: Digital Health Twin

**Platform:** Flutter (iOS/Android)
**Architecture:** Clean Architecture + BLoC (Business Logic Component)
**State Management:** flutter_bloc
**Networking:** Dio
**Real-time:** web_socket_channel

---

## Phase 1: Project Initialization & Infrastructure

### 1.1. Project Setup
- [ ] Initialize Flutter project: `flutter create --org com.healthtwin --project-name mobile_app .`
- [ ] Configure `analysis_options.yaml` for strict linting.
- [ ] Set up flavors (dev, prod) if necessary.

### 1.2. Dependencies
Add the following packages to `pubspec.yaml`:
- **State Management:** `flutter_bloc`, `equatable`, `get_it` (DI).
- **Networking:** `dio`, `retrofit` (optional, or manual), `json_annotation`, `json_serializable`.
- **UI:** `google_fonts`, `flutter_svg`, `fl_chart` (for graphs).
- **Storage:** `flutter_secure_storage` (for tokens), `shared_preferences`.
- **Real-time:** `web_socket_channel`.

### 1.3. Folder Structure (Clean Architecture)
```
lib/
├── core/                   # Core functionality (errors, utils, constants)
│   ├── constants/
│   ├── error/
│   ├── network/
│   └── utils/
├── data/                   # Data Layer
│   ├── datasources/        # Remote (API) and Local sources
│   ├── models/             # DTOs (Data Transfer Objects)
│   └── repositories/       # Repository Implementations
├── domain/                 # Domain Layer (Business Logic)
│   ├── entities/           # Core Business Objects
│   ├── repositories/       # Repository Interfaces
│   └── usecases/           # Business Use Cases
├── presentation/           # UI Layer
│   ├── bloc/               # Global BLoCs (Auth, Theme)
│   ├── pages/              # Screens
│   └── widgets/            # Reusable Widgets
└── main.dart
```

---

## Phase 2: Data Layer & Networking

### 2.1. Network Client
- [ ] Configure `Dio` instance with base URL (`https://api.health-twin.global/v1`).
- [ ] Implement Interceptors for:
    - Adding `Authorization: Bearer <token>` header.
    - Logging (for debug).
    - Error handling (converting HTTP errors to Domain Exceptions).

### 2.2. Data Models (DTOs)
Create JSON serializable models based on `api_spec.md`:
- [ ] `UserModel` (id, name, age, etc.)
- [ ] `MetricModel` (type, value, timestamp)
- [ ] `RecommendationModel` (id, type, priority, message)

### 2.3. Repositories (Data Layer)
- [ ] `AuthRepositoryImpl`: Handle login/logout, token storage.
- [ ] `UserRepositoryImpl`: Fetch/Update profile.
- [ ] `MetricsRepositoryImpl`: Send metrics.
- [ ] `RecommendationsRepositoryImpl`: Fetch recommendations.

---

## Phase 3: Authentication & User Profile

### 3.1. Domain Layer
- [ ] Define `User` entity.
- [ ] Define `AuthRepository` interface.
- [ ] Create UseCases: `Login`, `Logout`, `GetProfile`.

### 3.2. State Management (Auth)
- [ ] Create `AuthBloc`:
    - Events: `AuthStarted`, `LoggedIn`, `LoggedOut`.
    - States: `AuthInitial`, `AuthAuthenticated`, `AuthUnauthenticated`, `AuthLoading`.

### 3.3. UI Implementation
- [ ] **Login Screen:** Simple UI with mock login (since API spec doesn't detail auth endpoint, assume OAuth flow or mock for now).
- [ ] **Profile Screen:** Display user details (Name, Age, Conditions).
- [ ] **Edit Profile Screen:** Form to update user data (`PUT /user/profile`).

---

## Phase 4: Core Features (Dashboard & Metrics)

### 4.1. Metrics Ingestion
- [ ] **Domain:** `Metric` entity, `SendMetrics` UseCase.
- [ ] **UI:** Button/Form to simulate sending data from "wearable" (`POST /data/metrics`).

### 4.2. Dashboard UI
- [ ] Create `DashboardPage`.
- [ ] Implement `MetricsBloc` to manage state of health data.
- [ ] **Widgets:**
    - Summary Cards (Heart Rate, Steps).
    - Charts using `fl_chart` to visualize historical data (mocked or fetched if API supports history).

---

## Phase 5: Recommendations & Real-time

### 5.1. Recommendations
- [ ] **Domain:** `Recommendation` entity, `GetRecommendations` UseCase.
- [ ] **UI:** List view of recommendations (`GET /recommendations/current`).
- [ ] Visual distinction for priorities (High = Red, Normal = Green).

### 5.2. WebSocket Integration
- [ ] Implement `WebSocketService` connecting to `wss://api.health-twin.global/v1/stream`.
- [ ] Handle events: `alert`, `sync_status`.
- [ ] **UI:** Show In-App Notifications (Snackbars or overlay) when `alert` event is received.

---

## Phase 6: Testing & Polish

### 6.1. Testing
- [ ] Unit Tests for BLoCs and UseCases.
- [ ] Repository Tests (mocking Dio).

### 6.2. Polish
- [ ] Error handling UI (Retry buttons, Error messages).
- [ ] Loading states (Shimmer effects).
- [ ] Theme configuration (Light/Dark mode).
