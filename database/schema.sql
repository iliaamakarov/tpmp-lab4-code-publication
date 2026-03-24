-- Удаляем таблицы, если они существуют, чтобы избежать конфликтов
DROP TABLE IF EXISTS USERS;
DROP TABLE IF EXISTS CREW;
DROP TABLE IF EXISTS TRAWLERS;
DROP TABLE IF EXISTS TRIPS;
DROP TABLE IF EXISTS TRIP_RESULTS;
DROP TABLE IF EXISTS TRAWLER_STATS;
DROP TABLE IF EXISTS BONUSES;

-- Таблица пользователей для аутентификации
CREATE TABLE USERS (
    username TEXT PRIMARY KEY NOT NULL,
    password TEXT NOT NULL,
    role TEXT NOT NULL, -- 'captain' или 'crewman'
    crew_surname TEXT,
    FOREIGN KEY (crew_surname) REFERENCES CREW(surname)
);

-- Таблица членов экипажа
CREATE TABLE CREW (
    surname TEXT PRIMARY KEY NOT NULL,
    position TEXT NOT NULL, -- 'captain', 'sailor', 'cook'
    hire_date TEXT NOT NULL,
    birth_year INTEGER NOT NULL
);

-- Таблица траулеров
CREATE TABLE TRAWLERS (
    name TEXT PRIMARY KEY NOT NULL,
    displacement INTEGER NOT NULL,
    construction_date TEXT NOT NULL
);

-- Таблица рейсов
CREATE TABLE TRIPS (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    trawler_name TEXT NOT NULL,
    exit_date TEXT NOT NULL,
    return_date TEXT,
    FOREIGN KEY (trawler_name) REFERENCES TRAWLERS(name)
);

-- Таблица с результатами рейсов (улов)
CREATE TABLE TRIP_RESULTS (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    trip_id INTEGER NOT NULL,
    bank_name TEXT NOT NULL,
    fish_name TEXT NOT NULL,
    fish_quality TEXT NOT NULL, -- 'high', 'medium', 'low'
    fish_quantity_kg INTEGER NOT NULL,
    FOREIGN KEY (trip_id) REFERENCES TRIPS(id)
);

-- Таблица для хранения статистики по траулерам
CREATE TABLE TRAWLER_STATS (
    trawler_name TEXT PRIMARY KEY,
    total_fish_caught INTEGER DEFAULT 0,
    FOREIGN KEY (trawler_name) REFERENCES TRAWLERS(name)
);

-- Таблица для хранения рассчитанных премий
CREATE TABLE BONUSES (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    crew_surname TEXT NOT NULL,
    bonus_amount REAL NOT NULL,
    calculation_date TEXT NOT NULL,
    FOREIGN KEY (crew_surname) REFERENCES CREW(surname)
);

-- Триггер для обновления статистики после добавления улова
CREATE TRIGGER update_trawler_stats
AFTER INSERT ON TRIP_RESULTS
BEGIN
    UPDATE TRAWLER_STATS
    SET total_fish_caught = total_fish_caught + NEW.fish_quantity_kg
    WHERE trawler_name = (SELECT trawler_name FROM TRIPS WHERE id = NEW.trip_id);
END;
