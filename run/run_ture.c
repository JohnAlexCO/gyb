void run_ture(ture_t *ture){
    //ture_print_heap(ture);
    while (ture->ir < ture->kr) { step(ture); }
    //ture_print_state(ture);
}