#include <stdio.h>

#define MAX_SHELF_WEIGHT 500.0

// Cau truc thong tin kien hang pallet
typedef struct {
    int pallet_id;
    float weight_kg;
    float temp_celsius;
} PalletItem;

// Cau truc thong tin o ke kho
typedef struct {
    int shelf_id;
    int is_cold_storage;
    float current_weight_kg;
} WarehouseShelf;

// Kiem tra dieu kien an toan truoc khi nhap kho
int kiem_tra_an_toan_nhap_kho(WarehouseShelf shelf, PalletItem item) {
    // Kiem tra nhiet do neu la kho lanh
    if (shelf.is_cold_storage == 1) {
        if (item.temp_celsius < -18.0 || item.temp_celsius > 5.0) {
            printf("[LOI KHO LANH] Nhiet do %.1f C khong dat chuan "
                   "(-18 C den 5 C)!\n", item.temp_celsius);
            return 0;
        }
    }

    // Kiem tra tong tai trong sau khi xep them kien hang
    if (shelf.current_weight_kg + item.weight_kg > MAX_SHELF_WEIGHT) {
        printf("[LOI QUA TAI] Tong tai trong sau khi xep la %.1f kg, "
               "vuot gioi han %.1f kg!\n",
               shelf.current_weight_kg + item.weight_kg,
               MAX_SHELF_WEIGHT);
        return 0;
    }

    return 1;
}

int main() {
    // Ke 101 dang chua 400 kg hang trong kho lanh
    WarehouseShelf ke_lanh_101 = {101, 1, 400.0};

    // Kien hang moi nang 150 kg, nhiet do 12 C
    PalletItem pallet_moi = {5001, 150.0, 12.0};

    printf("=== HE THONG GIAM SAT AN TOAN NHAP KHO ===\n");

    printf("Thong tin ke %d: Tai trong hien tai = %.1f kg | Loai kho = %s\n",
           ke_lanh_101.shelf_id,
           ke_lanh_101.current_weight_kg,
           ke_lanh_101.is_cold_storage ? "Kho lanh" : "Kho thuong");

    printf("Kien hang: Ma = %d | Nang = %.1f kg | Nhiet do = %.1f C\n",
           pallet_moi.pallet_id,
           pallet_moi.weight_kg,
           pallet_moi.temp_celsius);

    printf("--------------------------------------------------\n");

    int ket_qua = kiem_tra_an_toan_nhap_kho(ke_lanh_101, pallet_moi);

    if (ket_qua == 1) {
        printf("KET QUA: [DUYET] Du dieu kien nhap kho!\n");
    } else {
        printf("KET QUA: [TU CHOI] Vi pham quy dinh an toan!\n");
    }

    return 0;
}