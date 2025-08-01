
module imageROM3 (
    
    input logic [10:0] pix_x,
    input logic [10:0] pix_y,
	 input logic [10:0] pos_y,
	 input logic [10:0] POSX,
    output logic paint
);

    // Declaración de señales internas
    logic [4:0] addRom_sig; //Row
    logic [39:0] dataRom_sig; //Col

    // Constantes para el tamaño de la ROM
    localparam int sizeColRom = 40;
    localparam int sizeRowRom = 24;

    // Instancia de la ROM (componente imageROM)
    ROM3 img3 (addRom_sig,dataRom_sig);

    // Proceso para dibujar la imagen almacenada en la ROM
    always_comb begin
        addRom_sig = 5'b00000;
        paint = 1'b0;

        if ((pix_y >=  pos_y) && (pix_y < ( pos_y + sizeRowRom)) &&
            (pix_x >= POSX) && (pix_x < (POSX + sizeColRom))) 
        begin
            addRom_sig = pix_y -  pos_y;
            paint = dataRom_sig[sizeColRom - 1-(pix_x -POSX)];
        end
    end

endmodule