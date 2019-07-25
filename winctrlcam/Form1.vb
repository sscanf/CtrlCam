Public Class Form1
    Inherits System.Windows.Forms.Form

#Region " Código generado por el Diseñador de Windows Forms "

    Public Sub New()
        MyBase.New()

        'El Diseñador de Windows Forms requiere esta llamada.
        InitializeComponent()

        'Agregar cualquier inicialización después de la llamada a InitializeComponent()

    End Sub

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms requiere el siguiente procedimiento
    'Puede modificarse utilizando el Diseñador de Windows Forms. 
    'No lo modifique con el editor de código.
    Friend WithEvents Arriba As System.Windows.Forms.Button
    Friend WithEvents abajo As System.Windows.Forms.Button
    Friend WithEvents izquierda As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(Form1))
        Me.Arriba = New System.Windows.Forms.Button()
        Me.abajo = New System.Windows.Forms.Button()
        Me.izquierda = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Arriba
        '
        Me.Arriba.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Arriba.ForeColor = System.Drawing.Color.FromArgb(CType(0, Byte), CType(54, Byte), CType(135, Byte))
        Me.Arriba.Image = CType(resources.GetObject("Arriba.Image"), System.Drawing.Bitmap)
        Me.Arriba.Location = New System.Drawing.Point(342, 141)
        Me.Arriba.Name = "Arriba"
        Me.Arriba.Size = New System.Drawing.Size(30, 24)
        Me.Arriba.TabIndex = 0
        '
        'abajo
        '
        Me.abajo.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.abajo.ForeColor = System.Drawing.Color.FromArgb(CType(0, Byte), CType(54, Byte), CType(135, Byte))
        Me.abajo.Image = CType(resources.GetObject("abajo.Image"), System.Drawing.Bitmap)
        Me.abajo.Location = New System.Drawing.Point(340, 235)
        Me.abajo.Name = "abajo"
        Me.abajo.Size = New System.Drawing.Size(30, 24)
        Me.abajo.TabIndex = 1
        '
        'izquierda
        '
        Me.izquierda.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.izquierda.ForeColor = System.Drawing.Color.FromArgb(CType(0, Byte), CType(54, Byte), CType(135, Byte))
        Me.izquierda.Image = CType(resources.GetObject("izquierda.Image"), System.Drawing.Bitmap)
        Me.izquierda.Location = New System.Drawing.Point(299, 189)
        Me.izquierda.Name = "izquierda"
        Me.izquierda.Size = New System.Drawing.Size(21, 24)
        Me.izquierda.TabIndex = 2
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Bitmap)
        Me.ClientSize = New System.Drawing.Size(520, 293)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.izquierda, Me.abajo, Me.Arriba})
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub

#End Region

End Class
