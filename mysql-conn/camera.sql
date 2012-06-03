-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 03 Cze 2012, 13:53
-- Wersja serwera: 5.5.16
-- Wersja PHP: 5.3.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `parking`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `camera`
--

CREATE TABLE IF NOT EXISTS `camera` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `parking_id` int(11) unsigned NOT NULL,
  `address` varchar(255) NOT NULL,
  `type` varchar(255) NOT NULL DEFAULT 'file',
  `last_scan` int(11) unsigned NOT NULL DEFAULT '0',
  `threshold_high` double unsigned NOT NULL DEFAULT '100',
  `threshold_low` double unsigned NOT NULL DEFAULT '3',
  `threshold_scan` double unsigned NOT NULL DEFAULT '0.125',
  `apeture_size` int(11) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `parking_id` (`parking_id`),
  KEY `ostatni_skan` (`last_scan`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Zrzut danych tabeli `camera`
--

INSERT INTO `camera` (`id`, `parking_id`, `address`, `type`, `last_scan`, `threshold_high`, `threshold_low`, `threshold_scan`, `apeture_size`) VALUES
(1, 1, 'C:/Users/tdroL/Documents/Visual Studio 2010/Projects/parking/assets/preview1.jpg', 'file', 0, 100, 3, 0.125, 1);

--
-- Ograniczenia dla zrzutów tabel
--

--
-- Ograniczenia dla tabeli `camera`
--
ALTER TABLE `camera`
  ADD CONSTRAINT `camera_ibfk_1` FOREIGN KEY (`parking_id`) REFERENCES `parking` (`id`) ON DELETE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
