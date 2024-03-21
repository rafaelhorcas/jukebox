# Jukebox

## Authors

* **Rafael Horcas Mateo** - email: [r.horcasm@alumnos.upm.es](mailto:r.horcasm@alumnos.upm.es)
* **Víctor Mendizábal Gimeno** - email: [v.mendizabal@alumnos.upm.es](mailto:v.mendizabal@alumnos.upm.es)

En el proyecto Jukebox se establece una comunicación a través de un puerto USART usando STM32F446RE conectado a un ordenador. Esto permite la comunicación con un zumbador que puede reproducir melodías y cuenta con funcionalidades que se van desarrollando a lo largo del proyecto.

The Jukebox project establishes communication via USART port using an STM32F446RE connected to a computer. This enables communication with a buzzer capable of playing melodies. It has more functionalities that are developed throughout the project.

## Version 1
En la primera versión solo está habilitado el botón de usuario, el cual está conectado al **pin 13** de la **GPIO C**. 

El sistema es capaz de identificar si se pulsa el botón y durante cuanto tiempo. Debido al funcionamiento del hardware del botón es necesario implementar un sistema anti-rebotes, que ha sido configurado a **150ms**. De esta manera, solo se pueden identificar como pulsaciones válidas aquellas con este tiempo mínimo.

Para la detección de las pulsaciones se ha empleado la interrupción externa 13 (EXTI13).

En la siguiente tabla se especifican las diferentes configuraciones necesarias para el correcto funcionamiento del botón de usuario.

| Parámetro | Valor | 
| --------- | --------- | 
| Pin   | PC13   | 
| Modo   | Input   | 
| Pull up/down   | No push no pull   | 
| EXTI   | EXTI13   | 
| ISR   | EXTI15_10_IRQHandler  | 
| Prioridad  | 1  |
| Subprioridad   | 0 | 
| Tiempo antirebotes| 150ms  | 

Para la implementación, en primer lugar, se ha desarrollado una librería basada en una máquina de estados finitos para el botón. Se puede observar el código en los siguientes ficheros:

Archivo de cabeceras: [fsm_button.h](fsm__button_8h.html) 

Archivo de código fuente: [fsm_button.c](fsm__button_8c.html)

A continuación, se ha desarrollado el código necesario en la parte portable para la placa STM32F446RE. Además, es posible añadir más botones si se desea para versiones posteriores.

Archivo de cabeceras: [port_button.h](port__button_8h.html) 

Archivo de código fuente: [port_button.c](port__button_8c.html)

## Version 2
En la segunda versión se habilita la comunicación serie entre la placa y el ordenador mediante una USART. Se va a usar la **USART3**. La transmisión, **TX**, se encuentra en la **GPIO B**, en el **pin 10** y la recepción, **RX**, se encuentra en la **GPIO C**, en el **pin 11**.

En la siguiente tabla se especifican las diferentes configuraciones necesarias para el correcto funcionamiento de la USART3.

| Parámetro | Valor | 
| --------- | --------- | 
| Baudrate   | 9600   | 
| Data bits   | 8   | 
| Stop bits  | 1   | 
| Parity   | None   | 
| Flow control   | None | 
| USART  | USART3 |
| Pins   | PB10 (TX) and PC11 (RX) | 
| Mode| Alternative |
| Pull up/down   | Pull up | 
| ISR   | USART3_IRQn | 
| Priority | 2  |
| Subpriority  | 0 | 

Para la implementación, en primer lugar, se ha desarrollado una librería basada en una máquina de estados finitos para la trasmisión de datos. Se puede observar el código en los siguientes ficheros:

Archivo de cabeceras: [fsm_usart.h](fsm__usart_8h.html) 

Archivo de código fuente: [fsm_usart.c](fsm__usart_8c.html)

A continuación, se ha desarrollado el código necesario en la parte portable para la placa STM32F446RE. Además, es posible añadir más USARTs si se desea para versiones posteriores.

Archivo de cabeceras: [port_usart.h](port__usart_8h.html) 

Archivo de código fuente: [port_usart.c](port__usart_8c.html)





**Las imágenes se deben guardar en la carpeta `docs/assets/imgs/` y se pueden incluir en el documento de la siguiente manera:**

```markdown
![Texto alternativo](docs/assets/imgs/imagen.png)
``` 

