# uuid
генератор UUID
Определятеся объект UUID. Это уникальное 16 байтовое число, которое известно как GUID. Все методы и функции потокобезопасны,
те могут использоваться в многопоточной среде. Алгоритм генерации инкрементальный со списком использованих UUID. Усли мы вызываем
функцию releaseUUID, то данный UUID заносится в этот список. В процессе генерации мы вначале выдаём UUID оттуда начиная
с последнего сохранённого там. Раземр свободных реализованных UUID можно получить функцией getNumberOfLostUUIDs. Сами UUID
являются упорядочеными. Поэтому допускают использование в таких контейнерах как set и map в качестве ключей для быстрого поиска.
Так же поддеживается инициализация произвольным массивом но в этом случае уникальность не гарантируется. Так же есть функция
getUUIDRnd для получения UUID сгенерированого генератором случайных чистел как обычно это сделано в генераторе GUID.
Кроме того есть метод toStr для получения строкового представления UUID как это принято в GUID
