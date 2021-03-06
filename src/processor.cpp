#include "../include/processor.hpp"

processor::processor(){
    this->mem = memory(_big, _hex, _hex);
    this->b_reg = registers();
}

processor::~processor() {
    this->mem.~memory();
    this->b_reg.~registers();
}

void processor::load_memory_text(const char *path, memory_section sec, unsigned int base) {
    fstream file_obj;
    char mem_block[11];
    int16_t i = 0;
    unsigned int start = sec == _text? 0: BASE_DATA_ADDRESS;

    file_obj.open(path, ios::in);
    if(file_obj.is_open()){
        while(!file_obj.eof()){
            file_obj.getline(mem_block, 10);
            this->mem.sw(start, i, (uint32_t)strtoul(mem_block, nullptr, base));
            i += _word;
        }
        file_obj.close();
    }
    else
        printf(UNKNOWN_FILE);
}

void processor::load_memory_binary(const char *path, memory_section sec) {
    fstream file_obj;
    uint32_t current_word;
    int16_t i = 0;
    unsigned int start = sec == _text? 0: BASE_DATA_ADDRESS;

    file_obj.open(path, ios::in|ios::binary);
    if(file_obj.is_open()){
        while(!file_obj.eof()){
            file_obj.read((char *)&current_word, sizeof(current_word));
            this->mem.sw(start, i, current_word);
            i+=_word;
        }
        this->mem.sw(start, i-_word, 0x00000000);
    }
    else
        printf(UNKNOWN_FILE);
}

void processor::fetch() {
    if(b_reg.PC < BASE_DATA_ADDRESS) {
        b_reg.RI = (uint32_t) mem.lw(b_reg.PC, 0);
        b_reg.update_pc(_word);
    }
    else
        throw out_of_range(PC_OUT_OF_BOUNDS);
}

void processor::decode() {
    this->inst_fields.opcode = (uint8_t)(b_reg.RI>>26);
    this->inst_fields.rs = (uint8_t)((b_reg.RI>>21) & 0x0000001F);
    this->inst_fields.rt = (uint8_t)((b_reg.RI>>16) & 0x0000001F);
    this->inst_fields.rd = (uint8_t)((b_reg.RI>>11) & 0x0000001F);
    this->inst_fields.shammt = (uint8_t)((b_reg.RI>>6) & 0x0000001F);
    this->inst_fields.funct = (uint8_t)((b_reg.RI) & 0x0000003F);
    this->inst_fields.k16 = (int16_t) (b_reg.RI & 0x0000FFFF);
    this->inst_fields.k26 = (uint32_t) (b_reg.RI & 0x03FFFFFF);
}

void processor::execute() {
    switch (this->inst_fields.opcode){
        case EXT:
            switch (this->inst_fields.funct){
                case ADD:
                    this->add();
                    break;
                case SUB:
                    this->sub();
                    break;
                case MULT:
                    this->mult();
                    break;
                case DIV:
                    this->div();
                    break;
                case AND:
                    this->_and();
                    break;
                case OR:
                    this->_or();
                    break;
                case XOR:
                    this->_xor();
                    break;
                case NOR:
                    this->nor();
                    break;
                case SLT:
                    this->slt();
                    break;
                case JR:
                    this->jr();
                    break;
                case SLL:
                    this->sll();
                    break;
                case SRL:
                    this->srl();
                    break;
                case SRA:
                    this->sra();
                    break;
                case SYSCALL:
                    this->syscall();
                    break;
                case MFHI:
                    this->mfhi();
                    break;
                case MFLO:
                    this->mflo();
                    break;
                default:
                    throw logic_error(UNKNOWN_OPCODE);
            }
            break;
        case LW:
            this->lw();
            break;
        case LB:
            this->lb();
            break;
        case LBU:
            this->lbu();
            break;
        case LH:
            this->lh();
            break;
        case LHU:
            this->lhu();
            break;
        case LUI:
            this->lui();
            break;
        case SW:
            this->sw();
            break;
        case SB:
            this->sb();
            break;
        case SH:
            this->sh();
            break;
        case BEQ:
            this->beq();
            break;
        case BNE:
            this->bne();
            break;
        case BLEZ:
            this->blez();
            break;
        case BGTZ:
            this->bgtz();
            break;
        case ADDI:
            this->addi();
            break;
        case ADDIU:
            this->addiu();
            break;
        case SLTI:
            this->slti();
            break;
        case SLTIU:
            this->sltiu();
            break;
        case ANDI:
            this->andi();
            break;
        case ORI:
            this->ori();
            break;
        case XORI:
            this->xori();
            break;
        case J:
            this->j();
            break;
        case JAL:
            this->jal();
            break;
        default:
            throw logic_error(UNKNOWN_OPCODE);
    }
}

void processor::step(unsigned int amount){
    try{
        for (int i=0; i< amount; i++){
            this->fetch();
            this->decode();
            this->execute();
        }
    }
    catch (const exception &exc){
        printf(exc.what());
    }
}

void processor::run(){
    while(true){
        try{
            this->fetch();
            this->decode();
            this->execute();
        }
        catch (const exception &exc){
            printf(exc.what());
            break;
        }
    }
}


