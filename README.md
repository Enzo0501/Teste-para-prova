# Teste-para-prova
-------------------------------------------
using Lista.Models;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<AppDataContext>();
var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.MapPost("/lista/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(tarefa.Nome))
    {
        return Results.BadRequest("O nome da tarefa é obrigatório.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/lista/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

app.MapGet("/lista/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

app.MapGet("/lista/tarefas/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    return Results.Ok(tarefa);
});

app.MapDelete("/lista/tarefas/deletar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    ctx.Tarefas.Remove(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});

app.Run();

+++++++

using Microsoft.EntityFrameworkCore;

namespace Lista.Models;

public class AppDataContext : DbContext
{
    public DbSet<Tarefa> Tarefas { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=app.db");
    }
}

++++++++++++++

namespace Lista.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}


--------------------------------------------------------
###Relacionamento entre tabelas### 

DB -

Um pra um
protected override void OnModelCreating(ModelBuilder modelBuilder)
{
    modelBuilder.Entity<Tabela2>()
        .HasOne(t => t.Tarefa)
        .WithOne()
        .HasForeignKey<Tabela2>(t => t.TarefaId);
}

protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Configuração do relacionamento um-para-muitos
            modelBuilder.Entity<Tabela2>()
                .HasOne(t => t.Tarefa)           // Uma Tabela2 tem uma Tarefa
                .WithMany(t => t.Tabela2s)       // Uma Tarefa tem muitas Tabela2
                .HasForeignKey(t => t.TarefaId); // A Foreign Key é TarefaId
        }
