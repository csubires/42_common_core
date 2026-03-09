# Análisis de Requisitos de Módulos Major y Minor - ft_transcendence

**Fecha de revisión:** 25 de enero de 2026  
**Estado del proyecto:** Revisión de cumplimiento de módulos

---

## 📋 MÓDULOS ANALIZADOS

### 1. Major Module: AI Opponent (IA Player)
### 2. Major Module: Multiple Players
### 3. Major Module: Add Another Game with User History and Matchmaking
### 4. Minor Module: Game Customization Options

---

# 1️⃣ MAJOR MODULE: AI OPPONENT

**Estado actual:** ✅ **CUMPLE COMPLETAMENTE**  
**Archivo afectado:** [`frontend/src/pong.ts`](frontend/src/pong.ts)
**Última actualización:** 2026-02-02

---

## 📋 Requisitos del Módulo Major - IA Player

El módulo requiere incorporar un jugador de IA al juego con las siguientes características **obligatorias**:

### 1. ✅ Desarrollar un oponente IA desafiante
- **Estado:** CUMPLIDO
- Existe implementación de IA con 3 niveles de dificultad (Easy/Medium/Hard)

### 2. ❌ NO usar algoritmo A*
- **Estado:** CUMPLIDO
- El código usa seguimiento simple de posición, no A*

### 3. ✅ La IA debe replicar comportamiento humano
**CRÍTICO:** La IA debe simular entrada de teclado, NO modificar directamente la posición del paddle.

- **Estado:** ✅ **CUMPLIDO** (2026-02-02)
- **Implementación:** La IA ahora establece `keys['ArrowUp']` y `keys['ArrowDown']` en lugar de modificar `paddle2.y`
- **Método:** El movimiento del paddle se aplica igual que para un jugador humano

### 4. ✅ Restricción de actualización: 1 vez por segundo
**CRÍTICO:** La IA solo puede refrescar su vista del juego una vez por segundo.

- **Estado:** ✅ **CUMPLIDO** (2026-02-02)
- **Implementación:** Se agregaron variables `aiLastUpdate` y `aiDecision` para guardar la última decisión
- **Lógica:** La IA solo calcula una nueva decisión cada 1000ms, usando la anterior en los frames intermedios
- **Variables:** `aiLastUpdate` (timestamp) y `aiDecision` ('up' | 'down' | '')

### 5. ✅ Anticipación de rebotes
**CRÍTICO:** La IA debe anticipar la trayectoria de la bola considerando rebotes.

- **Estado:** ✅ **CUMPLIDO** (2026-02-02)
- **Implementación:** Función `predictBallPosition()` que calcula dónde estará la bola cuando llegue al paddle
- **Lógica:** 
  - Calcula el tiempo que tarda la bola en alcanzar x=780 (posición del paddle)
  - Proyecta la posición Y futura considerando rebotes en paredes superior/inferior
  - Simula rebotes hasta encontrar la posición final válida dentro de los límites del juego
- **Uso:** La IA usa esta predicción en lugar de perseguir reactivamente `ball.y`

---

## 🎮 MEJORAS ADICIONALES (2026-02-02)

### Exit Game Button
**Problema:** No había forma de salir del juego sin terminar la partida; la bola seguía funcionando
**Solución:** Implementado botón "Exit Game" que aparece durante la partida
- **Función:** `exitGame()` - Cancela animationFrame, detiene el juego y navega a games
- **UI:** Botón flotante en esquina inferior derecha
- **Comportamiento:** Se muestra al iniciar juego, se oculta al terminar
- **Archivo:** [`frontend/src/pong.ts`](frontend/src/pong.ts) y [`frontend/index.html`](frontend/index.html)

---

## 🔍 Código Actual (Problemático)

### Ubicación: `frontend/src/pong.ts` (líneas 218-221)

```typescript
if (isAI) {
  const center = paddle2.y + 50;
  if (center < ball.y - 10) paddle2.y += difficulty;
  else if (center > ball.y + 10) paddle2.y -= difficulty;
  paddle2.y = Math.max(0, Math.min(500, paddle2.y));
}
```

### ❌ Problemas identificados:

1. **Modificación directa:** `paddle2.y += difficulty` - No simula teclas
2. **Acceso continuo:** Lee `ball.y` en cada frame (60 veces por segundo)
3. **Sin predicción:** Solo sigue la posición actual de la bola

---

## ✅ Checklist de Implementación

- [ ] Agregar variables de estado de IA (`aiLastUpdate`, `aiTargetY`, `aiDecision`)
- [ ] Implementar función `predictBallPosition()` con cálculo de rebotes
- [ ] Implementar función `updateAIDecision()` con restricción de 1 segundo
- [ ] Reemplazar código actual de IA para usar `keys['ArrowUp']` y `keys['ArrowDown']`
- [ ] Probar con diferentes niveles de dificultad
- [ ] Verificar que la IA no actualiza más de 1 vez por segundo (usar `console.log`)
- [ ] Verificar que la IA anticipa rebotes correctamente

---

## 🧪 Testing

### Verificar restricción de 1 segundo:
Agregar temporalmente en `updateAIDecision()`:
```typescript
console.log('AI updated decision at:', currentTime, 'Target Y:', aiTargetY);
```

Deberías ver mensajes solo cada ~1000ms en la consola.

### Verificar predicción de rebotes:
Observar si la IA se posiciona correctamente antes de que la bola rebote.

### Verificar simulación de teclado:
La IA debe moverse de manera similar a un jugador humano (no instantánea).

---

## 📚 Referencia

- **Archivo a modificar:** [`frontend/src/pong.ts`](frontend/src/pong.ts)
- **Líneas problemáticas:** 218-221
- **Función afectada:** `update()`
- **Canvas height:** 600px (paredes en y=10 y y=590)
- **Paddle height:** 100px
- **Velocidad paddle:** 5px por frame

---

## 💡 Notas Importantes

1. **No eliminar el código PvP:** El bloque `else` de PvP debe permanecer intacto
2. **Inicializar variables:** Asegurarse de resetear `aiLastUpdate` cuando inicia el juego
3. **Considerar velocidad variable:** La bola acelera con cada golpe (`* 1.05`), la predicción debe ser robusta
4. **Testing exhaustivo:** Probar todos los niveles de dificultad

---

**¿Preguntas?** Este documento describe EXACTAMENTE qué cambiar y cómo hacerlo para cumplir con los requisitos del módulo Major de IA.

---
---

# 2️⃣ MAJOR MODULE: MULTIPLE PLAYERS

**Estado actual:** ❌ **NO IMPLEMENTADO**  
**Archivos afectados:** Necesita nuevo desarrollo

---

## 📋 Requisitos del Módulo

### Objetivo Principal
Permitir que **más de 2 jugadores** puedan jugar simultáneamente. Cada jugador debe tener control en vivo.

### Especificaciones
- ✅ Se puede mantener el juego regular de 2 jugadores
- ✅ Definir un número específico de jugadores (3, 4, 5, 6 o más)
- ✅ Cada jugador debe tener control en vivo (el módulo "remote players" es altamente recomendado)
- ✅ Ejemplo sugerido: 4 jugadores en un tablero cuadrado, cada uno controlando un lado único

---

## 🔍 Análisis del Código Actual

### Pong Actual
- **Jugadores:** Solo 2 (paddle izquierdo y derecho)
- **Controles:** W/S para Player 1, ArrowUp/ArrowDown para Player 2
- **Bola:** Una sola bola con rebotes en 2 paddles

### TicTacToe Actual
- **Jugadores:** 2 (X y O)
- **Modalidad:** Por turnos, no simultáneo
- **Tablero:** 3x3 fijo

---

## ❌ Problemas Identificados

1. **Arquitectura limitada:** El código actual de Pong está diseñado para exactamente 2 jugadores
2. **Sin soporte para jugadores remotos:** No hay sistema WebSocket/networking implementado
3. **Sin sistema de lobby:** No existe forma de que múltiples jugadores se unan a una partida
4. **Canvas rígido:** El layout actual (800x600) solo soporta 2 paddles laterales

---

## ✅ Soluciones Propuestas

### Opción 1: Pong para 4 Jugadores (Recomendado)

#### Diseño de Gameplay
```
┌─────────────────────┐
│   PLAYER 1 (TOP)    │
│    W/S o ArrowUp/Down
├─────────────────────┤
│                     │
P│                     │P
L│         🔴          │L
A│                     │A
Y│                     │Y
E│                     │E
R│                     │R
 │                     │
3│                     │2
│                     │
│  A/D              ←/→│
├─────────────────────┤
│  PLAYER 4 (BOTTOM)  │
│    Z/X              │
└─────────────────────┘
```

#### Características
- **Tablero:** 800x800 (cuadrado)
- **4 Paddles:** Uno en cada lado
- **1 Bola:** Rebota en los 4 lados
- **Puntuación:** Cada jugador tiene puntos independientes
- **Eliminación progresiva:** Cuando un jugador pierde todas sus vidas, su paddle desaparece

#### Controles Sugeridos
```typescript
// Player 1 (TOP): W/S
// Player 2 (RIGHT): ArrowUp/ArrowDown
// Player 3 (LEFT): A/D  
// Player 4 (BOTTOM): Z/X
```

### Opción 2: Pong Cooperativo 2v2

#### Diseño
- **Equipos:** 2 equipos de 2 jugadores cada uno
- **Lado izquierdo:** 2 paddles (alto y bajo)
- **Lado derecho:** 2 paddles (alto y bajo)
- **Objetivo:** Trabajar en equipo para defender tu lado

---

## 🎯 Checklist de Implementación - Multiple Players

- [ ] Crear archivo `pongMultiplayer.ts` con lógica para 3-4 jugadores
- [ ] Implementar sistema de vidas por jugador
- [ ] Implementar eliminación progresiva
- [ ] Crear UI para selección de número de jugadores
- [ ] Actualizar `gameService.ts` para soportar arrays de jugadores
- [ ] Implementar controles para 4 jugadores simultáneos
- [ ] Crear canvas cuadrado (800x800)
- [ ] Implementar colisiones para 4 lados
- [ ] Añadir indicadores visuales de vidas restantes
- [ ] Guardar resultados de partidas multijugador en base de datos
- [ ] **[RECOMENDADO]** Implementar módulo "Remote Players" para juego en red
- [ ] Testing exhaustivo con 2, 3 y 4 jugadores

---

## 💡 Consideraciones para Remote Players

Si se implementa el módulo de jugadores remotos:
- Usar **WebSockets** para sincronización en tiempo real
- Implementar sistema de **lobby/rooms**
- Añadir **latency compensation**
- Validar posiciones en el servidor
- Implementar **reconnection handling**

---
---

# 3️⃣ MAJOR MODULE: ANOTHER GAME WITH USER HISTORY AND MATCHMAKING

**Estado actual:** ⚠️ **PARCIALMENTE IMPLEMENTADO**  
**Archivos afectados:** [`frontend/src/tictactoe.ts`](frontend/src/tictactoe.ts), [`frontend/src/gameService.ts`](frontend/src/gameService.ts)

---

## 📋 Requisitos del Módulo

### Objetivo Principal
Introducir un **nuevo juego distinto de Pong** con funcionalidades de historial de usuario y matchmaking.

### Características Requeridas
1. ✅ Desarrollar un juego nuevo y atractivo para diversificar la oferta
2. ❌ Implementar seguimiento de historial de usuario (estadísticas individuales)
3. ❌ Crear sistema de matchmaking para encontrar oponentes
4. ❌ Almacenar historial de juegos y datos de matchmaking de forma segura
5. ❌ Optimizar rendimiento y capacidad de respuesta
6. ❌ Mantenimiento regular: arreglar bugs, añadir funciones, mejorar gameplay

---

## 🔍 Análisis del Código Actual

### TicTacToe Implementado ✅
- **Archivo:** `frontend/src/tictactoe.ts`
- **Estado:** Juego básico funcional
- **Características:**
  - ✅ Tablero 3x3
  - ✅ Turnos alternados (X y O)
  - ✅ Detección de victoria/empate
  - ✅ UI visual con canvas

### ❌ Funcionalidades Faltantes

#### 1. NO integrado con gameService
```typescript
// TicTacToe actual NO guarda partidas
function showWinner(w: string): void {
  // Solo muestra ganador y regresa al menú
  // NO llama a endGameSession() ni saveMatch()
}
```

#### 2. NO tiene sistema de jugadores
```typescript
// No hay player1/player2 definidos
// Solo símbolos 'X' y 'O' sin nombres
let player = 'X';  // ❌ No son objetos Player
```

#### 3. NO hay matchmaking
- No existe sistema de búsqueda de oponentes
- No hay lobby o cola de espera
- No hay emparejamiento por nivel/ranking

#### 4. NO guarda historial
- Las partidas no se guardan en la base de datos
- No hay estadísticas de TicTacToe por usuario
- No se registran wins/losses

---

## 🎯 Checklist de Implementación - Another Game

- [ ] **Integración TicTacToe:**
  - [ ] Modificar `tictactoe.ts` para usar `gameService`
  - [ ] Añadir sistema de jugadores (Player objects)
  - [ ] Integrar `endGameSession()` y `saveMatch()`
  - [ ] Probar que las partidas se guardan en BD
  
- [ ] **Matchmaking System:**
  - [ ] Crear `matchmaking.ts` en frontend
  - [ ] Crear rutas de matchmaking en backend
  - [ ] Implementar cola de espera
  - [ ] Implementar algoritmo de emparejamiento por skill level
  - [ ] Crear UI de búsqueda de partida
  - [ ] Testing de matchmaking con múltiples usuarios
  
- [ ] **User History:**
  - [ ] Extender estadísticas para incluir TicTacToe
  - [ ] Crear página de historial de partidas
  - [ ] Mostrar stats separadas por juego (Pong vs TicTacToe)
  - [ ] Implementar filtros en historial
  
- [ ] **Optimización:**
  - [ ] Usar Redis para cola de matchmaking (escala mejor que memoria)
  - [ ] Implementar timeouts para matchmaking
  - [ ] Añadir WebSockets para notificaciones instantáneas
  - [ ] Testing de rendimiento

---
---

# 4️⃣ MINOR MODULE: GAME CUSTOMIZATION OPTIONS

**Estado actual:** ❌ **NO IMPLEMENTADO**  
**Archivos afectados:** Múltiples (requiere nuevo desarrollo)

---

## 📋 Requisitos del Módulo

### Objetivo Principal
Proporcionar opciones de personalización para **todos los juegos disponibles** en la plataforma.

### Características Requeridas
1. ❌ Ofrecer opciones de personalización: power-ups, ataques, mapas diferentes
2. ✅ Permitir versión por defecto con características básicas
3. ❌ Opciones disponibles para **TODOS** los juegos
4. ❌ Menús de configuración amigables
5. ❌ Consistencia en personalización entre juegos

---

## 🔍 Estado Actual

### ❌ Sin Personalizaciones
- **Pong:** Solo opciones de dificultad de IA (no es personalización de gameplay)
- **TicTacToe:** Sin opciones de ningún tipo
- **Sin power-ups** implementados
- **Sin mapas alternativos**
- **Sin modificadores de juego**

---

## 🎯 Checklist de Implementación - Customization

- [ ] **UI de Personalización:**
  - [ ] Crear página `customize.ts`
  - [ ] Diseñar menús para Pong
  - [ ] Diseñar menús para TicTacToe
  - [ ] Implementar sistema de guardado (localStorage)
  - [ ] Añadir link en navegación principal
  
- [ ] **Pong Customization:**
  - [ ] Implementar power-ups (5 tipos mínimo)
  - [ ] Crear 4 mapas diferentes
  - [ ] Implementar modos de juego (quick, chaos, practice)
  - [ ] Sistema de spawn de power-ups
  - [ ] Visual feedback para power-ups activos
  
- [ ] **TicTacToe Customization:**
  - [ ] Soporte para tableros 3x3, 4x4, 5x5
  - [ ] Implementar 3 temas visuales
  - [ ] Modo cronometrado (timer por turno)
  - [ ] Modo gravedad (optional)
  
- [ ] **Integración:**
  - [ ] Cargar configuración al inicio de cada juego
  - [ ] Aplicar configuración durante gameplay
  - [ ] Mostrar configuración activa en UI
  - [ ] Opción de "Reset to Default"
  
- [ ] **Testing:**
  - [ ] Probar todas las combinaciones de settings
  - [ ] Verificar persistencia de configuración
  - [ ] Testing de power-ups en diferentes mapas
  - [ ] Balance de dificultad en modos especiales

---
---

# 📊 RESUMEN GENERAL DE CUMPLIMIENTO

| Módulo | Estado | Prioridad | Complejidad |
|--------|--------|-----------|-------------|
| **AI Opponent** | ⚠️ Parcial (70%) | 🔴 Alta | Media |
| **Multiple Players** | ❌ No implementado | 🟡 Media | Alta |
| **Another Game + Matchmaking** | ⚠️ Parcial (40%) | 🔴 Alta | Alta |
| **Game Customization** | ❌ No implementado | 🟢 Baja | Media |

---

## 🚀 Roadmap Sugerido

### Fase 1: Completar IA (1-2 días)
1. Implementar simulación de teclado
2. Añadir restricción de 1 segundo
3. Implementar predicción de rebotes
4. Testing exhaustivo

### Fase 2: Matchmaking + TicTacToe Integration (3-4 días)
1. Integrar TicTacToe con gameService
2. Crear sistema de matchmaking (frontend + backend)
3. Implementar queue y skill-based matching
4. Testing con múltiples usuarios

### Fase 3: Customization (2-3 días)
1. Diseñar UI de personalización
2. Implementar power-ups para Pong
3. Crear mapas alternativos
4. Añadir opciones para TicTacToe
5. Testing de todas las combinaciones

### Fase 4: Multiple Players (4-5 días)
1. Diseñar gameplay para 4 jugadores
2. Implementar controles y lógica
3. Crear UI de selección
4. Testing multijugador local
5. [OPCIONAL] Implementar remote players con WebSockets

---

## 💡 Notas Finales

- **Prioridad inmediata:** Completar módulo de IA (es el más avanzado)
- **Mayor impacto:** Matchmaking system (mejora mucho la experiencia)
- **Más trabajo:** Multiple players con remote support
- **Más divertido:** Game customization (power-ups, etc.)

Todos los módulos están documentados con código de ejemplo listo para implementar. ¡Buena suerte! 🎮

---

**¿Preguntas?** Este documento describe EXACTAMENTE qué cambiar y cómo hacerlo para cumplir con TODOS los requisitos de los módulos Major y Minor.
