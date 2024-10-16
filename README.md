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

--------------------------------------------------
Criar uma Solution e API

dotnet new sln --output NomeDaSolução ->cd .\NomeSoluçao\

dotnet new web --name NomedaAPI
dentro da solucao
dotnet sln add NomedaAPI

dotnet run --project NomeApi
pegar http://localhost:5258
criar teste.http

criar pasta models
---
namespace Lista.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}
---
Dentro da API
dotnet add package Microsoft.EntityFrameworkCore.Sqlite
dotnet add package Microsoft.EntityFrameworkCore.Design


dotnet ef migrations add InitialCreate
dotnet ef database update
--------------------

using APITeste.Models;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddDbContext<AppDataContext>();
var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.MapPost("/apiteste/tarefas/cadastrar", ([FromBody] Tarefa tarefa, [FromServices] AppDataContext ctx) => 
{
    if (string.IsNullOrWhiteSpace(tarefa.Nome))
    {
        return Results.BadRequest("O nome da tarefa é obrigatório.");
    }

    ctx.Tarefas.Add(tarefa);
    ctx.SaveChanges();
    return Results.Created($"/apiteste/tarefas/buscar/{tarefa.TarefaId}", tarefa);
});

app.MapGet("/apiteste/tarefas/listar", ([FromServices] AppDataContext ctx) => 
{
    var tarefas = ctx.Tarefas.ToList();
    if (tarefas.Any())
    {
        return Results.Ok(tarefas);
    }
    return Results.NotFound("Nenhuma tarefa encontrada.");
});

app.MapGet("/apiteste/tarefas/buscar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    var tarefa = ctx.Tarefas.Find(id);
    if (tarefa == null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    return Results.Ok(tarefa);
});

app.MapDelete("/apiteste/tarefas/deletar/{id}", ([FromRoute] int id, [FromServices] AppDataContext ctx) => 
{
    Tarefa? tarefa = ctx.Tarefas.Find(id);
    if (tarefa is null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    ctx.Tarefas.Remove(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});

app.MapPut("/apiteste/tarefas/alterar/{id}", ([FromRoute] int id,
    [FromBody] Tarefa tarefaAlterada, 
    [FromServices] AppDataContext ctx) => 
{
    Tarefa? tarefa = ctx.Tarefas.Find(id);
    if (tarefa is null)
    {
        return Results.NotFound("Tarefa não encontrada.");
    }
    tarefa.Nome = tarefaAlterada.Nome;
    ctx.Tarefas.Update(tarefa);
    ctx.SaveChanges();
    return Results.Ok(tarefa);
});


app.Run();

--------

using Microsoft.EntityFrameworkCore;

namespace APITeste.Models;

public class AppDataContext : DbContext
{
    public DbSet<Tarefa> Tarefas { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite("Data Source=app.db");
    }
}
-------
namespace APITeste.Models;

public class Tarefa
{
    public int TarefaId { get; set; }
    public string? Nome { get; set; }
    public DateTime CriadoEm { get; set; } = DateTime.Now;
}




