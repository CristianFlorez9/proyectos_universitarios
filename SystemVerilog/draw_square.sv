module draw_square (
	 input logic  [10:0] posicion_ymax, //posiciones para ajustar el tamaño del cuadro
	 input logic  [10:0] posicion_ymim,
	 input logic  [10:0] posicion_xmax,
	 input logic  [10:0] posicion_xmin,
    input logic  [10:0] pix_x, //esto sale del modulo de vga -> investigar funcionamiento
    input logic  [10:0] pix_y, //esto sale del modulo de vga -> investigar funcionamiento
    input logic  [11:0] rgb_int, //color del cuadro 
	 input logic  [11:0] color_fondo,
    output logic [11:0] rgb_out // color afuera del cuadro (debe ser del mismo color que el fondo de la pantalla)
);

always_comb begin
    if ((pix_y >= posicion_ymim) && (pix_y <= posicion_ymax) 
	 && (pix_x >= posicion_xmin) && (pix_x <= posicion_xmax)) begin
        rgb_out = rgb_int;
    end else begin
        rgb_out = color_fondo;
    end
end

endmodule

