document.addEventListener("DOMContentLoaded", () =>{
    const title = document.querySelector(".title");
    title.style.opacity=0;
    title.style.transform = "translateY(-50px)";
    setTimeout(() => {
        title.style.transition = "all 1.5s ease";
        title.style.opacity = 1;
        title.style.transform = "translateY(0)";
    }, 500);
});

//Tentar implementar Scroll suave para seções
document.addEventListener("scroll", () =>{
    const resume = document.querySelector(".resume");


    const scrollY = window.scrollY;

    if(scrollY >200){
        resume.style.opacity ="1";
        resume.style.transform = "translateY(0)";

    } else{
        resume.style.opacity ="1";
        resume.style.transform ="translateY(20px)";
    }

    links.style.transition = "all 0.5s ease-in-out";
})

//Implementar expansão tabela

document.getElementById("toggleTableBtn1").addEventListener("click", () => {
    const cs50Table1 = document.getElementById("cs50Table1");
    if (cs50Table1.style.display === "none") {
        cs50Table1.style.display = "block";
        toggleTableBtn1.innerHTML = 'CS50 &#9650;';
    } else {
        cs50Table1.style.display = "none";
        toggleTableBtn1.innerHTML = 'CS50 &#9660;';
    }
});


document.addEventListener("DOMContentLoaded", () => {
    // Tabela CS50 já configurada

    // Botão para Tabela Blockchain
    const toggleBlockchainTableBtn = document.getElementById("toggleBlockchainTableBtn");
    const blockchainTable = document.getElementById("blockchainTable");

    toggleBlockchainTableBtn.addEventListener("click", () => {
        if (blockchainTable.style.display === "none") {
            blockchainTable.style.display = "block";
            toggleBlockchainTableBtn.innerHTML = 'Blockchain e Smart Contracts &#9650;'; // Seta para cima
        } else {
            blockchainTable.style.display = "none";
            toggleBlockchainTableBtn.innerHTML = 'Blockchain e Smart Contracts &#9660;'; // Seta para baixo
        }
    });
});
