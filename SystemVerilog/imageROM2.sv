module imageROM2 (
    input logic [10:0] POSX,    
    input logic [10:0] pos_y,    
    input logic [10:0] pix_x,
    input logic [10:0] pix_y,
    output logic paint
);

    // Señales internas
    logic [4:0] addRom_sig;
    logic [39:0] dataRom_sig;

    // Tamaño de la imagen ROM
    localparam int sizeColRom = 40;
    localparam int sizeRowRom = 24;

    // Instancia de la ROM que contiene la imagen
    ROM2 img2 (addRom_sig, dataRom_sig);

    // Lógica para pintar la imagen
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
